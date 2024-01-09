

#ifdef EUCALYPTUS_PLATFORM_WINDOWS
#ifdef _EUCDLL
#define _EUCAPI __declspec(dllexport)
#else
#define _EUCAPI __declspec(dllimport)
#endif
#elif defined(EUCALYPTUS_PLATFORM_LINUX)
#ifdef _EUCDLL
#define _EUCAPI __attribute__((visibility("default")))
#else
#define _EUCAPI
#endif
#else
#error Eucalyptus doesnt support your platform. Have you set the EUCALYPTUS_PLATFORM_<platform> compiler flag?
#define _EUCAPI
#endif