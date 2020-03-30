/*
    Lightmetrica - Copyright (c) 2019 Hisanari Otsu
    Distributed under MIT license. See LICENSE file for details.
*/

#pragma once

#include <lm/logger.h>
#pragma warning(push)
#pragma warning(disable:4324)   // structure was padded due to alignment specifier
#include <embree3/rtcore.h>
#pragma warning(pop)
LM_NAMESPACE_BEGIN(LM_NAMESPACE)

static void handle_embree_error(void*, RTCError code, const char* str = nullptr) {
    if (code == RTC_ERROR_NONE) {
        return;
    }

    std::string codestr;
    switch (code) {
        case RTC_ERROR_UNKNOWN:           { codestr = "RTC_ERROR_UNKNOWN"; break; }
        case RTC_ERROR_INVALID_ARGUMENT:  { codestr = "RTC_ERROR_INVALID_ARGUMENT"; break; }
        case RTC_ERROR_INVALID_OPERATION: { codestr = "RTC_ERROR_INVALID_OPERATION"; break; }
        case RTC_ERROR_OUT_OF_MEMORY:     { codestr = "RTC_ERROR_OUT_OF_MEMORY"; break; }
        case RTC_ERROR_UNSUPPORTED_CPU:   { codestr = "RTC_ERROR_UNSUPPORTED_CPU"; break; }
        case RTC_ERROR_CANCELLED:         { codestr = "RTC_ERROR_CANCELLED"; break; }
        default:                          { codestr = "Invalid error code"; break; }
    }

    LM_ERROR("Embree error [code='{}']", codestr);
    if (str) {
        LM_INDENT();
        LM_ERROR(str);
    }

    LM_THROW_EXCEPTION(Error::None, codestr);
}

void from_json(const lm::Json& j, RTCSceneFlags& sf);
void to_json(lm::Json &j, const RTCSceneFlags& sf);
void from_json(const lm::Json& j, RTCBuildArguments& rtc);
void to_json(lm::Json &j, const RTCBuildArguments& rtc);

inline std::string RTCtoStr(const RTCBuildArguments& rtc, const RTCSceneFlags& sf)
{
        std::string str = fmt::format(
        "\nbuildQuality:\t{}\n"
        "maxBranchingFactor:\t{}\n"
        "maxDepth:\t{}\n"
        "sahBlockSize:\t{}\n"
        "minLeafSize:\t{}\n"
        "maxLeafSize:\t{}\n"
        "traversalCost:\t{}\n"
        "intersectionCost:\t{}\n",
        "dynamic:\t{}\n"
        "compact:\t{}\n"
        "robust:\t{}\n"
        "filter:\t{}\n",
        rtc.buildQuality, rtc.maxBranchingFactor, rtc.maxDepth, rtc.sahBlockSize, rtc.minLeafSize,
        rtc.maxLeafSize, rtc.traversalCost, rtc.intersectionCost,
        sf & (1<<0),sf &(1<<1),sf&(1<<2),sf&(1<<3));
        
       
        
        return str;
    }
LM_NAMESPACE_END(LM_NAMESPACE)