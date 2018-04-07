#pragma once

#include <avisynth.h>

struct FuncDefinition {
  typedef IScriptEnvironment::ApplyFunc apply_func_t;

   const char* name;
   const char* params;
   apply_func_t func;
   void* user_data;

   FuncDefinition(void*)
     : FuncDefinition(nullptr, nullptr, nullptr, nullptr, nullptr) { }
   FuncDefinition(const char* name, const char* _not_used, const char* params, apply_func_t func)
     : FuncDefinition(name, _not_used, params, func, nullptr) { }
   FuncDefinition(const char* name, const char* _not_used, const char* params, apply_func_t func, void *user_data)
     : name(name), params(params), func(func), user_data(user_data) { }
};

#define BUILTIN_FUNC_PREFIX "dummy"

int GetDeviceTypes(const PClip& clip);

void Copy(BYTE* dstp, int dst_pitch, const BYTE* srcp, int src_pitch, int row_size, int height, IScriptEnvironment2* env);

#ifndef NDEBUG
//#if 1
#define DEBUG_SYNC \
CUDA_CHECK(cudaGetLastError()); \
CUDA_CHECK(cudaDeviceSynchronize())
#else
#define DEBUG_SYNC
#endif

#define IS_CUDA (env->GetProperty(AEP_DEVICE_TYPE) == DEV_TYPE_CUDA)
