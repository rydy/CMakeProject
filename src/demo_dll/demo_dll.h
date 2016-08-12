#if defined(__cplusplus)
extern "C" {
#endif

#if defined(_WIN32) || defined(_WIN64)
#  ifndef DEMO_DLL_EXPORTS
#    define DEMO_DLL_API __declspec(dllimport)
#  else
#    define DEMO_DLL_API __declspec(dllexport)
#  endif
#  define DEMO_DLL_CALL __stdcall
#elif defined(__unix) || defined(__linux)
#  define DEMO_DLL_API
#  define DEMO_DLL_CALL
#endif

DEMO_DLL_API int DEMO_DLL_CALL Func(int a, int b);

#if defined(__cplusplus)
}
#endif
