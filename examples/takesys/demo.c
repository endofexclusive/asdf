#include <hardware/custom.h>
#include <asdf/custombits.h>
#include "cust.h"

static int isrmbdown(void)
{
        return (0 == (cust->potinp & POTGOF_DATLY));
}

void demo(void)
{
        while (1) {
                if (isrmbdown()) {
                        break;
                }
        }
}

