#ifndef __SIMPLE_KERN_LEVELS_H__
#define __SIMPLE_KERN_LEVELS_H__

#define KERN_SOH      "\001"

#define KERN_EMERG      KERN_SOH "EMERG: "    /* 0 denotes a unstable system */
#define KERN_ALERT      KERN_SOH "ALERT: "    /* 1 action must be taken immediately */
#define KERN_CRIT       KERN_SOH "CRIT: "     /* 2 critical conditions */
#define KERN_ERR        KERN_SOH "ERR: "      /* 3 error conditions */
#define KERN_WARNING    KERN_SOH "EMERG: "    /* 4 warning conditions */
#define KERN_NOTICE     KERN_SOH "NOTICE: "   /* 5 normal but significant condition */
#define KERN_INFO       KERN_SOH "INFO: "     /* 6 informational */
#define KERN_DEBUG      KERN_SOH "DEBUG: "    /* 7 debug-level messages */

#define KERN_DEFAULT    ""

#define KERN_CONT       KERN_SOH "CONT: "

#endif
