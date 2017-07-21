/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-05-22 Mon 20:27:08
 * @description: 
 * 
 */
#ifndef ENV_H
#define ENV_H

#if defined(_WIN32) ||  defined(WIN32) || defined(_WIN64) || defined(WIN64)
#define WINDOWS_PLATFORM

#elif defined(__GNUC__) || defined(linux) || defined(__linux)
#define LINUX_PLATFORM

#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#define FREEBSD_PLATFORM

#endif


#endif // ENV_H
