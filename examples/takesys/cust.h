#ifndef CUST_H_
#define CUST_H_

#define CUSTOMBASE 0xdff000

/*
 * Global register variable is a GCC extension which associates a variable with
 * a specific register. For this to work, the definition MUST be available to
 * ALL compilation units, since otherwise the register may be clobbered. See
 * the GCC manual for more information.
 *
 * Define CUSTOM_AS_GLOBAL_REG to enable CUSTOMBASE as global register.
 */
#ifndef CUSTOM_AS_GLOBAL_REG
 #define CUSTOM_AS_GLOBAL_REG 0
#endif

#if CUSTOM_AS_GLOBAL_REG
 register volatile struct Custom *cust asm ("a5");
 static inline void cust_init(void) { cust = (void *) CUSTOMBASE; }
#else
 static volatile struct Custom *const cust = (void *) CUSTOMBASE;
 static inline void cust_init(void) { }
#endif

#endif

