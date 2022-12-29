#ifndef VK_MSG_SESSION_UTILS
#define VK_MSG_SESSION_UTILS

#include <X11/Xlib.h>
#include <malloc.h>

#define VK_SESSION_PROPERTY	"_SGI_VK_SESSION"

#ifdef __cplusplus			/* do not leave open across includes */
extern "C" {					/* for C++ V2.0 */
#endif

extern char *VkMsgGetWindowIDSession(Display *dpy, char *window);

extern char *VkMsgGetWindowSession(Display *dpy, Window win);

extern char *VkMsgSelectWindowSession(Display *dpy);

#ifdef __cplusplus
}
#endif

#endif
