
#ifndef SN3DDLPDEV_EXPORT_H
#define SN3DDLPDEV_EXPORT_H

#ifdef SN3DDLPDEV_STATIC_DEFINE
#  define SN3DDLPDEV_EXPORT
#  define SN3DDLPDEV_NO_EXPORT
#else
#  ifndef SN3DDLPDEV_EXPORT
#    ifdef sn3DDLPdev_EXPORTS
        /* We are building this library */
#      define SN3DDLPDEV_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define SN3DDLPDEV_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef SN3DDLPDEV_NO_EXPORT
#    define SN3DDLPDEV_NO_EXPORT 
#  endif
#endif

#ifndef SN3DDLPDEV_DEPRECATED
#  define SN3DDLPDEV_DEPRECATED __declspec(deprecated)
#endif

#ifndef SN3DDLPDEV_DEPRECATED_EXPORT
#  define SN3DDLPDEV_DEPRECATED_EXPORT SN3DDLPDEV_EXPORT SN3DDLPDEV_DEPRECATED
#endif

#ifndef SN3DDLPDEV_DEPRECATED_NO_EXPORT
#  define SN3DDLPDEV_DEPRECATED_NO_EXPORT SN3DDLPDEV_NO_EXPORT SN3DDLPDEV_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef SN3DDLPDEV_NO_DEPRECATED
#    define SN3DDLPDEV_NO_DEPRECATED
#  endif
#endif

#endif
