/**
 * cpuid.c
 *
 * Checks if CPU has support of AES instructions
 *
 * @author kryukov@frtk.ru
 * @version 4.0
 *
 * For Putty AES NI project
 * http://putty-aes-ni.googlecode.com/
 */

#include <stdio.h>

#if defined(__clang__) || defined(__GNUC__)

#include <cpuid.h>
static int CheckCPUsupportAES()
{
    unsigned int CPUInfo[4];
    __cpuid(1, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
    return (CPUInfo[2] & (1 << 25)) && (CPUInfo[2] & (1 << 19)); /* Check AES and SSE4.1 */
}

#else /* defined(__clang__) || defined(__GNUC__) */

static int CheckCPUsupportAES()
{
    unsigned int CPUInfo[4];
    __cpuid(CPUInfo, 1);
    return (CPUInfo[2] & (1 << 25)) && (CPUInfo[2] & (1 << 19)); /* Check AES and SSE4.1 */
}

#endif /* defined(__clang__) || defined(__GNUC__) */

int main(int argc, char ** argv)
{
    const int res = !CheckCPUsupportAES();
    printf("This CPU %s AES-NI\n", res ? "does not support" : "supports");
    return res;
}
