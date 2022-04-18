/*===========================================================================

  Copyright (c) 2012 Qualcomm Technologies Incorporated.  
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================*/

#include <assert.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#include "rpm_estimator.h"
#include "swevent.h"
#include "cpu.h"
#include "rpm_config.h"
#include "rpm_hash.h"
#include "CoreVerify.h"

#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))
#define DIFF(a,b)     (((a) < (b)) ? ((b)-(a)) : ((a)-(b)))

static uint32_t cpu2_estimate_2_5k_memory[0x280] __attribute__((used));

Estimator::Estimator()
  : selectedClock_(0)
{
    // Clear clock information, indicating we haven't seen one yet.
    memset(clockFreqkHz_, 0, sizeof(clockFreqkHz_));
}

void Estimator::updateClockRate(unsigned int clockFreqkHz)
{
    unsigned int min_diff       = 0xFFFFFFFF;
    unsigned int min_diff_point = 0;

    for(unsigned int i = 0; i < ARRAY_SIZE(clockFreqkHz_); i++)
    {
        if(clockFreqkHz_[i])
        {
            unsigned int diff = DIFF(clockFreqkHz, clockFreqkHz_[i]);
            if(!diff)
            {
              // Exact match.  Use this operating point.
              selectedClock_ = i;
              return;
            }
            else if(diff < min_diff)
            {
                min_diff = diff;
                min_diff_point = i;
            }
        }
        else
        {
            selectedClock_ = i;
            clockFreqkHz_[i] = clockFreqkHz;
            return;
        }
    }

    // No exact match an no open space to track a new point, so group it with the closest.
    selectedClock_ = min_diff_point;
}

Estimator &theEstimator()
{
    static Estimator rpm_estimator;
    return rpm_estimator;
}

EstimateCache::EstimateCache(uint32_t cache_size)
    : cacheSeq_(0)
{
    cacheSize_ = cache_size;
    cache_ = (CacheEntry*)malloc(sizeof(CacheEntry) * cache_size);
    memset(cache_, 0, sizeof(CacheEntry) * cache_size);
}

bool EstimateCache::lookup(uint32_t systemState, uint32_t actionHash, uint32_t *resultState, uint32_t *timeEstimate)
{
    // Our lookups aren't really a hash table at the moment, more of a list of hash values.
    // Search the cache checking for data about this pair.
    for(unsigned int i = 0; i < cacheSize_; ++i)
    {
        if(systemState == cache_[i].systemTag && actionHash == cache_[i].actionTag)
        {
            cache_[i].usedSeq = ++cacheSeq_;
            *resultState = cache_[i].resultState;
            *timeEstimate = cache_[i].estimate;

            SWEVENT(RPM_ESTIMATE_CACHE_HIT, cache_[i].estimate);
            return true;
        }
    }

    // We didn't find anything for this entry.
    return false;
}

void EstimateCache::observe(uint32_t startState, uint32_t actionHash, uint32_t resultState, uint32_t elapsed, bool save_estimate)
{
    // Our lookups aren't really a hash table at the moment, more of a list of hash values.
    unsigned int lru = 0, lruAge = 0;

    if(resultState != startState)
    {
        SWEVENT(RPM_ESTIMATE_CACHE_OBSERVE, startState, actionHash, resultState, elapsed);
        // First, look through the cache checking for an existing entry for this pair.
        for(unsigned int i = 0; i < cacheSize_; ++i)
        {
            if(startState == cache_[i].systemTag && actionHash == cache_[i].actionTag)
            {
                if(!save_estimate)
                {
                    //this "observe" is an SVS calculated observation based on an actual NOM observation
                    //if an SVS observation already exists, no need to overwrite it with a calculation
                    return;
                }
                if(resultState != cache_[i].resultState)
                {
                    SWEVENT(RPM_ESTIMATE_CACHE_MISMATCH, cache_[i].resultState, cache_[i].estimate, resultState, elapsed);

                    cache_[i].resultState = resultState;
                    cache_[i].estimate = elapsed;
                }
                else if(elapsed > cache_[i].estimate)
                {
                    cache_[i].estimate = elapsed;
                }
                cache_[i].usedSeq = ++cacheSeq_;
                return;
            }

            // Didn't match on this one, but keep track of the lru entry as we search.
            unsigned int age = cacheSeq_ - cache_[i].usedSeq;
            if(age > lruAge)
            {
                lru = i;
                lruAge = age;
            }
        }

        //assert(startState != resultState);
        // Didn't find an existing entry--stomp on the LRU entry.
        cache_[lru].systemTag = startState;
        cache_[lru].actionTag = actionHash;
        cache_[lru].resultState = resultState;
        cache_[lru].estimate = elapsed;
        cache_[lru].usedSeq = ++cacheSeq_;

        //if we are saving a FAST estimate for a transition at NOM, also save an SVS estimate 
        // assuming one doesn't exist already
        cpu_mode_id mode = cpu_current_speed();
        CORE_VERIFY(mode != CPU_SLOW2);
        if(CPU_FAST == mode)
        {
            unsigned fast_freq = cpu_get_freq(CPU_FAST);
            unsigned slow_freq = cpu_get_freq(CPU_SLOW);
            unsigned updated_system_state = rpm_resource_hash(startState, &rpm->resources[rpm->supported_resources], 
                                             sizeof(unsigned), &fast_freq, &slow_freq); //compute start state with SVS slow

            observe(updated_system_state, actionHash, resultState, ((4*elapsed) / 3), false);
        }
    }
}

EstimateCache &theEstimateCacheImmediate(void)
{
    static EstimateCache rpm_estimate_cache_immediate = (*(new EstimateCache(8)));
    return rpm_estimate_cache_immediate;
}

EstimateCache &theEstimateCache(void)
{
    static EstimateCache rpm_estimate_cache = (*(new EstimateCache(32)));
    return rpm_estimate_cache;
}

