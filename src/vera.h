#pragma once

#include "veda.h"
#include "vera_enums.h"
#include "vera_types.h"

#ifndef __cplusplus
#error "VERA requires C++!"
#else

#define veraLaunchKernel(...)	vedaLaunchKernel(__VA_ARGS__)
#define VERA2VEDA(P)		VEDAdeviceptr((uint64_t)P)

//------------------------------------------------------------------------------
veraError_t	veraInit		(void);
veraError_t	veraDeviceReset		(void);
veraError_t	veraGetDeviceProperties	(veraDeviceProp* prop, int device);
veraError_t	veraMalloc3D		(veraPitchedPtr* pitchedDevPtr, veraExtent extent);
veraError_t	veraMemcpy		(void* dst, const void* src, size_t count, veraMemcpyKind kind);
veraError_t	veraMemcpy2D		(void* dst, size_t dpitch, const void* src, size_t spitch, size_t width, size_t height, veraMemcpyKind kind);
veraError_t	veraMemcpy2DAsync	(void* dst, size_t dpitch, const void* src, size_t spitch, size_t width, size_t height, veraMemcpyKind kind, veraStream_t stream = 0);
veraError_t	veraMemcpyAsync		(void* dst, const void* src, size_t count, veraMemcpyKind kind, veraStream_t stream = 0);
veraError_t	veraMemset2D		(void* devPtr, size_t pitch, int value, size_t width, size_t height);
veraError_t	veraMemset2DAsync	(void* devPtr, size_t pitch, int value, size_t width, size_t height, veraStream_t stream = 0);
veraError_t	veraMemset3D		(veraPitchedPtr pitchedDevPtr, int value, veraExtent extent);
veraError_t	veraMemset3DAsync	(veraPitchedPtr pitchedDevPtr, int value, veraExtent extent, veraStream_t stream = 0);
veraError_t	veraPointerGetAttributes(veraPointerAttributes* attributes, const void* ptr);
veraError_t	veraSetDevice		(int device);
veraError_t	veraSetValidDevices	(int* device_arr, int len);
veraError_t	veraStreamAddCallback	(veraStream_t stream, veraStreamCallback_t callback, void* userData, unsigned int flags);
//------------------------------------------------------------------------------
// implementation of VERA API functions
/**
 * \defgroup veraapi VERA API
 *
 * To use VERA API functions, include "vera.h" header.
 */
/** @{ */

//------------------------------------------------------------------------------
/**
 * @brief Returns the string representation of an error code enum name.
 * @param error Error code to convert to string
 * @return Returns the string representation of an error code enum name.\n 
 *
 * Returns a string containing the name of an error code in the enum.
 * If the error code is not recognized, "unrecognized error code" is returned.
 */
inline const char*	veraGetErrorName	(veraError_t error)							{	const char* str; vedaGetErrorName(error, &str); return str;					}
//------------------------------------------------------------------------------
/**
 * @brief Returns the description string for an error code.
 * @param error Error code to convert to string
 * @return Returns the description string for an error code.\n 
 *
 * Returns the description string for an error code.
 * If the error code is not recognized, "unrecognized error code" is returned.
 */
inline const char*	veraGetErrorString	(veraError_t error)							{	const char* str; vedaGetErrorString(error, &str); return str;					}

//------------------------------------------------------------------------------
/**
 * @brief Returns information about the VEDA device.
 * @param value Returned VEDA device attribute value.
 * @param attr VEDA Device attribute to query.
 * @param device VEDA device handle.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.\n 
 *
 * Returns in *pi the integer value of the attribute attrib on device dev. The
 * supported attributes are:\n 
 * VEDA_DEVICE_ATTRIBUTE_SINGLE_TO_DOUBLE_PRECISION_PERF_RATIO: VEDA precision ratio.\n 
 * VEDA_DEVICE_ATTRIBUTE_CLOCK_RATE: Clock chip clock frequency of the VEDA device.\n 
 * VEDA_DEVICE_ATTRIBUTE_CLOCK_BASE: Clock Base clock frequency of the VEDA device.\n 
 * VEDA_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT: Number of VE cores corresponding to
 * VEDA device.\n 
 * VEDA_DEVICE_ATTRIBUTE_MEMORY_CLOCK_RATE: Clock memory clock frequency of the
 * VEDA device.\n 
 * VEDA_DEVICE_ATTRIBUTE_L1D_CACHE_SIZE: Size of the L1 cache of the device of VEDA device.\n 
 * VEDA_DEVICE_ATTRIBUTE_L1I_CACHE_SIZE: Size of L1 instruction cache of the VEDA device.\n 
 * VEDA_DEVICE_ATTRIBUTE_L2_CACHE_SIZE: Size of L2 data cache of the VEDA device.\n 
 * VEDA_DEVICE_ATTRIBUTE_LLC_CACHE_SIZE: Size of last level cache of the VEDA device.\n 
 * VEDA_DEVICE_ATTRIBUTE_MODEL: VE device model corresponding to VEDA device.\n 
 * VEDA_DEVICE_ATTRIBUTE_ABI_VERSION: VE device ABI version corresponding to VEDA device.\n 
 * VEDA_DEVICE_ATTRIBUTE_FIREWARE_VERSION: VE device firmware version corresponding to
 * VEDA device.
 */
inline veraError_t	veraDeviceGetAttribute	(int* value, veraDeviceAttr attr, int device)				{	CVEDA(veraInit()); return vedaDeviceGetAttribute(value, (VEDAdevice_attribute)attr, device);	}
//------------------------------------------------------------------------------
/**
 * @brief Returns a VE device power corresponding to VEDA Device.
 * @param temp pointer to hold the VE device power.
 * @param device VEDA device handle.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.\n 
 *
 * Calculated VE device power includes both the PCIe edge power as well as the VE
 * device AUX power with added 5W.
 */
inline veraError_t	veraDeviceGetPower	(float* temp, int device)						{	CVEDA(veraInit()); return vedaDeviceGetPower(temp, device);					}
//------------------------------------------------------------------------------
/**
 * @brief Retrieve the core temperature of the VEDA device in Celsius.
 * @param temp pointer to hold the core temperature.
 * @param coreIdx Core index of the VEDA device.
 * @param device VEDA device ID.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 */
inline veraError_t	veraDeviceGetTemp	(float* temp, const int coreIdx, int device)				{	CVEDA(veraInit()); return vedaDeviceGetTemp(temp, coreIdx, device);				}
//------------------------------------------------------------------------------
/**
 * @brief Block for a context's tasks to complete.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 * @retval VEDA_ERROR_UNKNOWN_CONTEXT VEDA context is not set for the calling thread.
 * @retval VEDA_ERROR_CONTEXT_IS_DESTROYED VEDA current context is already destroyed.\n 
 *
 * Blocks until the device has completed all preceding requested tasks.\n 
 * vedaCtxSynchronize() returns an error if one of the preceding tasks failed.
 */
inline veraError_t	veraDeviceSynchronize	(void)									{	CVEDA(veraInit()); return vedaCtxSynchronize();							}
//------------------------------------------------------------------------------
/**
 * @brief Return the latest AVEO version supported by VEDA.
 * @param driverVersion Pointer to hold the AVEO version.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 */
inline veraError_t	veraDriverGetVersion	(const char** driverVersion)						{	CVEDA(veraInit()); return vedaDriverGetVersion(driverVersion);					}
//------------------------------------------------------------------------------
/**
 * @brief Frees device memory.
 * @param devPtr Pointer to memory to free.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 * @retval VEDA_ERROR_UNKNOWN_CONTEXT VEDA context is not set for the calling thread.
 * @retval VEDA_ERROR_CONTEXT_IS_DESTROYED VEDA current context is already destroyed.\n 
 *
 * Frees the memory space pointed to by dptr, which must have been returned by a
 * previous call to vedaMemAlloc() or vedaMemAllocPitch().
 */
inline veraError_t	veraFree		(void* devPtr)								{	CVEDA(veraInit()); return vedaMemFree(VERA2VEDA(devPtr));					}
//------------------------------------------------------------------------------
/**
 * @brief Frees device memory with stream ordered semantics.
 * @param devPtr Pointer to memory to free.
 * @param stream The stream establishing the stream ordering contract.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 * @retval VEDA_ERROR_UNKNOWN_CONTEXT VEDA context is not set for the calling thread.
 * @retval VEDA_ERROR_CONTEXT_IS_DESTROYED VEDA current context is already destroyed.\n 
 *
 * Inserts a free operation into stream. The allocation must not be accessed after
 * stream execution reaches the free. After this API returns, accessing the memory
 * from any subsequent work launched on the VEDA device or querying its pointer
 * attributes results in undefined behavior.
 */
inline veraError_t	veraFreeAsync		(void* devPtr, veraStream_t stream = 0)					{	CVEDA(veraInit()); return vedaMemFreeAsync(VERA2VEDA(devPtr), stream);			}
//------------------------------------------------------------------------------
/**
 * @brief Frees host memory.
 * @param ptr Pointer to memory to free.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 * @retval VEDA_ERROR_UNKNOWN_CONTEXT VEDA context is not set for the calling thread.
 * @retval VEDA_ERROR_CONTEXT_IS_DESTROYED VEDA current context is already destroyed.\n 
 *
 * Frees the memory space pointed to by dptr, which must have been returned by a
 * previous call to vedaMemAllocHost().
 */
inline veraError_t	veraFreeHost		(void* ptr)								{	CVEDA(veraInit()); return vedaMemFreeHost(ptr);							}
//------------------------------------------------------------------------------
/**
 * @brief Returns the device ID for the current context.
 * @param device Returned device ID for the current context.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 * @retval VEDA_ERROR_UNKNOWN_CONTEXT VEDA context is not set for the calling thread.
 * @retval VEDA_ERROR_CONTEXT_IS_DESTROYED VEDA current context is already destroyed.\n 
 *
 * Returns in *device the ordinal of the current context's device.
 */
inline veraError_t	veraGetDevice		(int* device)								{	CVEDA(veraInit()); return vedaCtxGetDevice(device);						}
//------------------------------------------------------------------------------
/**
 * @brief Retrieve the number of initializaed VEDA device.
 * @param count pointer to hold the count of the VEDA device.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 */
inline veraError_t	veraGetDeviceCount	(int* count)								{	CVEDA(veraInit()); return vedaDeviceGetCount(count);						}
//------------------------------------------------------------------------------
/**
 * @brief Allocates host memory.
 * @param pHost Returned host pointer
 * @param size Requested allocation size in bytes.
 * @param flags
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 * @retval VEDA_ERROR_UNKNOWN_CONTEXT VEDA context is not set for the calling thread.
 * @retval VEDA_ERROR_CONTEXT_IS_DESTROYED VEDA current context is already destroyed.
 * @retval VEDA_ERROR_OUT_OF_MEMORY Host memory exausted.
 */
inline veraError_t	veraHostAlloc		(void** pHost, size_t size, unsigned int flags)				{	CVEDA(veraInit()); return vedaMemAllocHost(pHost, size);					}
//------------------------------------------------------------------------------
/**
 * @brief Enqueues a host function call in a stream.
 * @param stream Stream Identifier.
 * @param fn The function to call once preceding stream operations are complete.
 * @param userData User-specified data to be passed to the function.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_UNKNOWN_CONTEXT VEDA context is not set for the calling thread.
 * @retval VEDA_ERROR_CONTEXT_IS_DESTROYED VEDA current context is already destroyed.\n 
 *
 * Enqueues a host function to run in a stream. The function will be called after
 * currently enqueued work and will block work added after it.
 */
inline veraError_t	veraLaunchHostFunc	(veraStream_t stream, veraHostFn_t fn, void* userData)			{	CVEDA(veraInit()); return vedaLaunchHostFunc(stream, fn, userData);				}
//------------------------------------------------------------------------------
/**
 * @brief Allocates VEDA device memory.
 * @param devPtr Returned VEDA device pointer
 * @param size Requested allocation size in bytes.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 * @retval VEDA_ERROR_UNKNOWN_CONTEXT VEDA context is not set for the calling thread.
 * @retval VEDA_ERROR_CONTEXT_IS_DESTROYED VEDA current context is already destroyed.
 * @retval VEDA_ERROR_OUT_OF_MEMORY VEDA device memory exausted.\n 
 *
 * Allocates size bytes of linear memory on the VEDA device and returns in *ptr a
 * pointer to the allocated memory.
 */
inline veraError_t	veraMalloc		(void** devPtr, size_t size)						{	CVEDA(veraInit()); return vedaMemAlloc((VEDAdeviceptr*)devPtr, size);				}
//------------------------------------------------------------------------------
/**
 * @brief Allocates memory with stream ordered semantics.
 * @param devPtr Returned VEDA device pointer
 * @param size Requested allocation size in bytes.
 * @param stream The stream establishing the stream ordering contract and the
 * memory pool to allocate from
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 * @retval VEDA_ERROR_UNKNOWN_CONTEXT VEDA context is not set for the calling thread.
 * @retval VEDA_ERROR_CONTEXT_IS_DESTROYED VEDA current context is already destroyed.
 * @retval VEDA_ERROR_OUT_OF_MEMORY VEDA device memory exausted.\n 
 *
 * Inserts an allocation operation into stream. A pointer to the allocated memory
 * is returned immediately in *ptr. The allocation must not be accessed until
 * the the allocation operation completes.
 */
inline veraError_t	veraMallocAsync		(void** devPtr, size_t size, veraStream_t stream = 0)			{	CVEDA(veraInit()); return vedaMemAllocAsync((VEDAdeviceptr*)devPtr, size, stream);		}
//------------------------------------------------------------------------------
/**
 * @brief Allocates host memory.
 * @param ptr Returned host pointer
 * @param size Requested allocation size in bytes.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 * @retval VEDA_ERROR_UNKNOWN_CONTEXT VEDA context is not set for the calling thread.
 * @retval VEDA_ERROR_CONTEXT_IS_DESTROYED VEDA current context is already destroyed.
 * @retval VEDA_ERROR_OUT_OF_MEMORY Host memory exausted.
 */
inline veraError_t	veraMallocHost		(void** ptr, size_t size)						{	CVEDA(veraInit()); return vedaMemAllocHost(ptr, size);						}
//------------------------------------------------------------------------------
/**
 * @brief Allocates pitched device memory.
 * @param devPtr Returned device pointer
 * @param pitch Returned pitch of allocation in bytes.
 * @param width Requested allocation width in bytes
 * @param height Requested allocation height in rows
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 * @retval VEDA_ERROR_UNKNOWN_CONTEXT VEDA context is not set for the calling thread.
 * @retval VEDA_ERROR_CONTEXT_IS_DESTROYED VEDA current context is already destroyed.
 * @retval VEDA_ERROR_OUT_OF_MEMORY Host memory exausted.\n 
 *
 * Allocates at least WidthInBytes * Height bytes of linear memory on the device and
 * returns in *dptr a pointer to the allocated memory. The pitch returned in *pPitch
 * by vedaMemAllocPitch() is the width in bytes of the allocation.
 */
inline veraError_t	veraMallocPitch		(void** devPtr, size_t* pitch, size_t width, size_t height)		{	CVEDA(veraInit()); return vedaMemAllocPitch((VEDAdeviceptr*)devPtr, pitch, width, height, 1);	}
//------------------------------------------------------------------------------
/**
 * @brief Gets free and total memory.
 * @param free Returned free memory in bytes.
 * @param total Returned total memory in bytes.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 * @retval VEDA_ERROR_UNKNOWN_CONTEXT VEDA context is not set for the calling thread.
 * @retval VEDA_ERROR_CONTEXT_IS_DESTROYED VEDA current context is already destroyed.\n 
 *
 * Returns in *total the total amount of memory available to the the current context.
 * Returns in *free the amount of memory on the VEDA device that is free.
 */
inline veraError_t	veraMemGetInfo		(size_t* free, size_t* total)						{	CVEDA(veraInit()); return vedaMemGetInfo(free, total);						}
//------------------------------------------------------------------------------
/**
 * @brief Initializes device memory.
 * @param devPtr Destination device pointer.
 * @param value Value to set.
 * @param count Number of Elements.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 * @retval VEDA_ERROR_UNKNOWN_CONTEXT VEDA context is not set for the calling thread.
 * @retval VEDA_ERROR_CONTEXT_IS_DESTROYED VEDA current context is already destroyed.\n 
 *
 * Sets the memory range of N 32-bit values to the specified value us.
 */
inline veraError_t	veraMemset		(void* devPtr, int value, size_t count)					{	CVEDA(veraInit()); return vedaMemsetD32(VERA2VEDA(devPtr), value, count);			}
//------------------------------------------------------------------------------
/**
 * @brief Initializes device memory.
 * @param devPtr Destination device pointer.
 * @param value Value to set.
 * @param count Number of Elements.
 * @param stream The stream establishing the stream ordering contract.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 * @retval VEDA_ERROR_UNKNOWN_CONTEXT VEDA context is not set for the calling thread.
 * @retval VEDA_ERROR_CONTEXT_IS_DESTROYED VEDA current context is already destroyed.\n 
 *
 * Sets the memory range of N 32-bit values to the specified value us.
 */
inline veraError_t	veraMemsetAsync		(void* devPtr, int value, size_t count, veraStream_t stream = 0)	{	CVEDA(veraInit()); return vedaMemsetD32Async(VERA2VEDA(devPtr), value, count, stream);		}
//------------------------------------------------------------------------------
/**
 * @brief Return the VE address of the VEDA device function located in VEDA module.
 * @param func Buffer to hold the VE address of the VEDA device function.
 * @param mod handle to the VEDA module corresponding to the VE device code.
 * @param name Name of the VEDA device function for which the VE address is required.
 * @return VEDA_SUCCESS on Success
 * @return VEDA_ERROR_NOT_INITIALIZED If VEDA device is not initialized.
 * @return VEDA_ERROR_INVALID_VALUE In case the name of the VEDA device function is passed as NULL.
 * @return VEDA_ERROR_FUNCTION_NOT_FOUND Internal error from the AVEO library
 */
inline veraError_t	veraModuleGetFunction	(veraFunction_t* func, veraModule_t mod, const char* name)		{	CVEDA(veraInit()); return vedaModuleGetFunction(func, mod, name);				}
//------------------------------------------------------------------------------
/**
 * @brief To unload/remove the VE device code from the VE memory.
 * @param mod Pointer to the VEDA module corresponding to the VE device code..
 * @return VEDA_SUCCESS on Success
 * @return VEDA_ERROR_NOT_INITIALIZED If VEDA device is not initialized.
 * @return VEDA_ERROR_UNKOWN_CONTEXT If VEDA context is not initialized.
 */
inline veraError_t	veraModuleUnload	(veraModule_t mod)							{	CVEDA(veraInit()); return vedaModuleUnload(mod);						}
//------------------------------------------------------------------------------
/**
 * @brief To load the VE device code into the VE memory.
 * @param mod Pointer to hold the reference of the VEDA module.
 * @param name Library name of the file name containing VE device code.
 * @return VEDA_SUCCESS on Success
 * @return VEDA_ERROR_NOT_INITIALIZED If VEDA device is not initialized.
 * @return VEDA_ERROR_INVALID_VALUE If the provided VE library name is not valid.
 * @return VEDA_ERROR_MODULE_NOT_FOUND Internal error from the AVEO library
 */
inline veraError_t	veraModuleLoad		(veraModule_t* mod, const char* name)					{	CVEDA(veraInit()); return vedaModuleLoad(mod, name);						}
//------------------------------------------------------------------------------
/**
 * @brief Return the latest AVEO version supported by VEDA.
 * @param runtimeVersion Pointer to hold the AVEO version.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 */
inline veraError_t	veraRuntimeGetVersion	(const char** runtimeVersion)						{	CVEDA(veraInit()); return veraDriverGetVersion(runtimeVersion);					}
//------------------------------------------------------------------------------
/**
 * @brief Gets the VEDA SM count.
 * @param cnt pointer to hold the VEDA SM count.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 * @retval VEDA_ERROR_UNKNOWN_CONTEXT VEDA context is not set for the calling thread.
 * @retval VEDA_ERROR_CONTEXT_IS_DESTROYED VEDA current context is already destroyed.\n 
 *
 * Returns the VEDA SM count of the VEDA context bound to the calling CPU thread.
 */
inline veraError_t	veraStreamCnt		(int* cnt)								{	CVEDA(veraInit()); return vedaCtxStreamCnt(cnt);						}
//------------------------------------------------------------------------------
/**
 * @brief Determine status of a compute stream.
 * @param stream Determine status of a compute stream.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 * @retval VEDA_ERROR_UNKNOWN_CONTEXT VEDA context is not set for the calling thread.
 * @retval VEDA_ERROR_CONTEXT_IS_DESTROYED VEDA current context is already destroyed.\n 
 *
 * Returns CUDA_SUCCESS if all operations in the stream specified by hStream
 * have completed
 */
inline veraError_t	veraStreamQuery		(veraStream_t stream)							{	CVEDA(veraInit()); return vedaStreamQuery(stream);						}
//------------------------------------------------------------------------------
/**
 * @brief Wait until a stream's tasks are completed.
 * @param stream Determine status of a compute stream.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 * @retval VEDA_ERROR_UNKNOWN_CONTEXT VEDA context is not set for the calling thread.
 * @retval VEDA_ERROR_CONTEXT_IS_DESTROYED VEDA current context is already destroyed.\n 
 *
 * Waits until the device has completed all operations in the stream specified by
 * hStream.
 */
inline veraError_t	veraStreamSynchronize	(veraStream_t stream)							{	CVEDA(veraInit()); return vedaStreamSynchronize(stream);					}

//------------------------------------------------------------------------------
/**
 * @brief Returns a veraExtent based on input parameters.
 * @param w	Width in elements when referring to array memory, in bytes when referring to linear memory
 * @param h Height in elements
 * @param d Depth in elements
 * @return Returns a veraExtent based on input parameters.\n 
 *
 * Returns a veraExtent based on the specified input parameters w, h, and d.
 */
inline veraExtent make_veraExtent(size_t w, size_t h, size_t d) {
	veraExtent extent;
	extent.depth	= d;
	extent.height	= h;
	extent.width	= w;
	return extent;
}

//------------------------------------------------------------------------------
/**
 * @brief Returns a veraPitchedPtr based on input parameters.
 * @param d Pointer to allocated memory
 * @param p Pitch of allocated memory in bytes
 * @param xsz Logical width of allocation in elements
 * @param ysz Logical height of allocation in elements
 * @return Returns a veraPitchedPtr based on input parameters\n 
 *
 * Returns a veraPitchedPtr based on the specified input parameters d, p, xsz, and ysz.
 */
inline veraPitchedPtr make_veraPitchedPtr(void* d, size_t p, size_t xsz, size_t ysz) {
	veraPitchedPtr ptr;
	ptr.ptr		= d;
	ptr.pitch	= p;
	ptr.xsize	= xsz;
	ptr.ysize	= ysz;
	return ptr;
}
/** @} */

//------------------------------------------------------------------------------
#endif

// Unsupported API
#if 0
veraError_t 	veraGetLastError					(void);
veraError_t 	veraPeekAtLastError					(void);
veraError_t	veraChooseDevice					(int* device, const veraDeviceProp* prop);
veraError_t	veraStreamWaitEvent					(veraStream_t stream, cudaEvent_t event, unsigned int flags);
veraError_t	veraMemcpy3D						(const cudaMemcpy3DParms* p);
veraError_t	veraMemcpy3DAsync					(const cudaMemcpy3DParms* p, veraStream_t stream = 0);
veraError_t	veraMallocManaged					(void** devPtr, size_t size, unsigned int flags = cudaMemAttachGlobal);
veraError_t	veraMemRangeGetAttribute				(void* data, size_t dataSize, cudaMemRangeAttribute attribute, const void* devPtr, size_t count);
veraError_t	veraMemRangeGetAttributes				(void** data, size_t* dataSizes, cudaMemRangeAttribute ** attributes, size_t numAttributes, const void* devPtr, size_t count);
veraError_t	veraMemPrefetchAsync					(const void* devPtr, size_t count, int dstDevice, veraStream_t stream = 0);
veraError_t	veraThreadExchangeStreamCaptureMode			(cudaStreamCaptureMode ** mode);
veraError_t	veraMalloc3DArray					(cudaArray_t* array, const cudaChannelFormatDesc* desc, veraExtent extent, unsigned int flags);
veraError_t	veraMallocArray						(cudaArray_t* array, const cudaChannelFormatDesc* desc, size_t width, size_t height, unsigned int flags);
veraError_t	cudaArrayGetInfo					(cudaChannelFormatDesc* desc, veraExtent* extent, unsigned int* flags, cudaArray_t array);
veraError_t	cudaCtxResetPersistingL2Cache				(void);
veraError_t	cudaDestroyExternalMemory				(cudaExternalMemory_t extMem);
veraError_t	cudaDestroyExternalSemaphore				(cudaExternalSemaphore_t extSem);
veraError_t	cudaDeviceCanAccessPeer					(int* canAccessPeer, int device, int peerDevice);
veraError_t	cudaDeviceDisablePeerAccess				(int peerDevice);
veraError_t	cudaDeviceEnablePeerAccess				(int peerDevice, unsigned int flags);
veraError_t	cudaDeviceGetByPCIBusId					(int* device, const char* pciBusId);
veraError_t	cudaDeviceGetCacheConfig				(cudaFuncCache ** pCacheConfig);
veraError_t	cudaDeviceGetLimit					(size_t* pValue, cudaLimit limit);
veraError_t	cudaDeviceGetNvSciSyncAttributes			(void* nvSciSyncAttrList, int device, int flags);
veraError_t	cudaDeviceGetP2PAttribute				(int* value, cudaDeviceP2PAttr attr, int srcDevice, int dstDevice);
veraError_t	cudaDeviceGetPCIBusId					(char* pciBusId, int len, int device);
veraError_t	cudaDeviceGetSharedMemConfig				(cudaSharedMemConfig ** pConfig);
veraError_t	cudaDeviceGetStreamPriorityRange			(int* leastPriority, int* greatestPriority);
veraError_t	cudaDeviceSetCacheConfig				(cudaFuncCache cacheConfig);
veraError_t	cudaDeviceSetLimit					(cudaLimit limit, size_t value);
veraError_t	cudaDeviceSetSharedMemConfig				(cudaSharedMemConfig config);
veraError_t	cudaEventCreate						(cudaEvent_t* event);
veraError_t	cudaEventCreateWithFlags				(cudaEvent_t* event, unsigned int flags);
veraError_t	cudaEventDestroy					(cudaEvent_t event);
veraError_t	cudaEventElapsedTime					(float* ms, cudaEvent_t start, cudaEvent_t end);
veraError_t	cudaEventQuery						(cudaEvent_t event);
veraError_t	cudaEventRecord						(cudaEvent_t event, veraStream_t stream = 0);
veraError_t	cudaEventSynchronize					(cudaEvent_t event);
veraError_t	cudaExternalMemoryGetMappedBuffer			(void** devPtr, cudaExternalMemory_t extMem, const cudaExternalMemoryBufferDesc* bufferDesc);
veraError_t	cudaFreeArray						(cudaArray_t array);
veraError_t	cudaFreeMipmappedArray					(cudaMipmappedArray_t mipmappedArray);
veraError_t	cudaFuncGetAttributes					(cudaFuncAttributes* attr, const void* func);
veraError_t	cudaFuncSetAttribute					(const void* func, cudaFuncAttribute attr, int value);
veraError_t	cudaFuncSetCacheConfig					(const void* func, cudaFuncCache cacheConfig);
veraError_t	cudaFuncSetSharedMemConfig				(const void* func, cudaSharedMemConfig config);
veraError_t	cudaGetDeviceFlags					(unsigned int* flags);
veraError_t	cudaGetMipmappedArrayLevel				(cudaArray_t* levelArray, cudaMipmappedArray_const_t mipmappedArray, unsigned int level);
veraError_t	cudaGetSymbolAddress					(void** devPtr, const void* symbol);
veraError_t	cudaGetSymbolSize					(size_t* size, const void* symbol);
veraError_t	cudaHostGetDevicePointer				(void** pDevice, void* pHost, unsigned int flags);
veraError_t	cudaHostGetFlags					(unsigned int* pFlags, void* pHost);
veraError_t	cudaHostRegister					(void* ptr, size_t size, unsigned int flags);
veraError_t	cudaHostUnregister					(void* ptr);
veraError_t	cudaImportExternalMemory				(cudaExternalMemory_t* extMem_out, const cudaExternalMemoryHandleDesc* memHandleDesc);
veraError_t	cudaImportExternalSemaphore				(cudaExternalSemaphore_t* extSem_out, const cudaExternalSemaphoreHandleDesc* semHandleDesc);
veraError_t	cudaIpcCloseMemHandle					(void* devPtr);
veraError_t	cudaIpcGetEventHandle					(cudaIpcEventHandle_t* handle, cudaEvent_t event);
veraError_t	cudaIpcGetMemHandle					(cudaIpcMemHandle_t* handle, void* devPtr);
veraError_t	cudaIpcOpenEventHandle					(cudaEvent_t* event, cudaIpcEventHandle_t handle);
veraError_t	cudaIpcOpenMemHandle					(void** devPtr, cudaIpcMemHandle_t handle, unsigned int flags);
veraError_t	cudaLaunchCooperativeKernel				(const void* func, dim3 gridDim, dim3 blockDim, void** args, size_t sharedMem, veraStream_t stream = 0);
veraError_t	cudaLaunchCooperativeKernelMultiDevice			(cudaLaunchParams* launchParamsList, unsigned int numDevices, unsigned int flags);
veraError_t	cudaMallocMipmappedArray				(cudaMipmappedArray_t* mipmappedArray, const cudaChannelFormatDesc* desc, veraExtent extent, unsigned int numLevels, unsigned int flags);
veraError_t	cudaMemAdvise						(const void* devPtr, size_t count, cudaMemoryAdvise advice, int device);
veraError_t	cudaMemcpy2DArrayToArray				(cudaArray_t dst, size_t wOffsetDst, size_t hOffsetDst, cudaArray_const_t src, size_t wOffsetSrc, size_t hOffsetSrc, size_t width, size_t height, veraMemcpyKind kind = cudaMemcpyDeviceToDevice);
veraError_t	cudaMemcpy2DFromArray					(void* dst, size_t dpitch, cudaArray_const_t src, size_t wOffset, size_t hOffset, size_t width, size_t height, veraMemcpyKind kind);
veraError_t	cudaMemcpy2DFromArrayAsync				(void* dst, size_t dpitch, cudaArray_const_t src, size_t wOffset, size_t hOffset, size_t width, size_t height, veraMemcpyKind kind, veraStream_t stream = 0);
veraError_t	cudaMemcpy2DToArray					(cudaArray_t dst, size_t wOffset, size_t hOffset, const void* src, size_t spitch, size_t width, size_t height, veraMemcpyKind kind);
veraError_t	cudaMemcpy2DToArrayAsync				(cudaArray_t dst, size_t wOffset, size_t hOffset, const void* src, size_t spitch, size_t width, size_t height, veraMemcpyKind kind, veraStream_t stream = 0);
veraError_t	cudaMemcpy3DPeer					(const cudaMemcpy3DPeerParms* p);
veraError_t	cudaMemcpy3DPeerAsync					(const cudaMemcpy3DPeerParms* p, veraStream_t stream = 0);
veraError_t	cudaMemcpyFromSymbol					(void* dst, const void* symbol, size_t count, size_t offset, veraMemcpyKind kind = cudaMemcpyDeviceToHost);
veraError_t	cudaMemcpyFromSymbolAsync				(void* dst, const void* symbol, size_t count, size_t offset, veraMemcpyKind kind, veraStream_t stream = 0);
veraError_t	cudaMemcpyPeer						(void* dst, int dstDevice, const void* src, int srcDevice, size_t count);
veraError_t	cudaMemcpyPeerAsync					(void* dst, int dstDevice, const void* src, int srcDevice, size_t count, veraStream_t stream = 0);
veraError_t	cudaMemcpyToSymbol					(const void* symbol, const void* src, size_t count, size_t offset, veraMemcpyKind kind = cudaMemcpyHostToDevice);
veraError_t	cudaMemcpyToSymbolAsync					(const void* symbol, const void* src, size_t count, size_t offset, veraMemcpyKind kind, veraStream_t stream = 0);
veraError_t	cudaOccupancyAvailableDynamicSMemPerBlock		(size_t* dynamicSmemSize, const void* func, int numBlocks, int blockSize);
veraError_t	cudaOccupancyMaxActiveBlocksPerMultiprocessor		(int* numBlocks, const void* func, int blockSize, size_t dynamicSMemSize);
veraError_t	cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags	(int* numBlocks, const void* func, int blockSize, size_t dynamicSMemSize, unsigned int flags);
veraError_t	cudaSetDeviceFlags					(unsigned int flags);
veraError_t	cudaSetDoubleForDevice					(double* d);
veraError_t	cudaSetDoubleForHost					(double* d);
veraError_t	cudaSignalExternalSemaphoresAsync			(const cudaExternalSemaphore_t* extSemArray, const cudaExternalSemaphoreSignalParams* paramsArray, unsigned int numExtSems, veraStream_t stream = 0);
veraError_t	cudaStreamAttachMemAsync				(veraStream_t stream, void* devPtr, size_t length, unsigned int flags = cudaMemAttachSingle);
veraError_t	cudaStreamBeginCapture					(veraStream_t stream, cudaStreamCaptureMode mode);
veraError_t	cudaStreamCopyAttributes				(veraStream_t dst, veraStream_t src);
veraError_t	cudaStreamCreateWithFlags				(veraStream_t* pStream, unsigned int flags);
veraError_t	cudaStreamCreateWithPriority				(veraStream_t* pStream, unsigned int flags, int priority);
veraError_t	cudaStreamEndCapture					(veraStream_t stream, cudaGraph_t* pGraph);
veraError_t	cudaStreamGetAttribute					(veraStream_t hStream, cudaStreamAttrID attr, cudaStreamAttrValue* value_out);
veraError_t	cudaStreamGetCaptureInfo				(veraStream_t stream, cudaStreamCaptureStatus ** pCaptureStatus, unsigned long long* pId);
veraError_t	cudaStreamGetFlags					(veraStream_t hStream, unsigned int* flags);
veraError_t	cudaStreamGetPriority					(veraStream_t hStream, int* priority);
veraError_t	cudaStreamIsCapturing					(veraStream_t stream, cudaStreamCaptureStatus ** pCaptureStatus);
veraError_t	cudaStreamSetAttribute					(veraStream_t hStream, cudaStreamAttrID attr, const cudaStreamAttrValue* value);
veraError_t	cudaWaitExternalSemaphoresAsync				(const cudaExternalSemaphore_t* extSemArray, const cudaExternalSemaphoreWaitParams* paramsArray, unsigned int numExtSems, veraStream_t stream = 0);
cudaPos		make_cudaPos						(size_t x, size_t y, size_t z);
void*		cudaGetParameterBuffer					(size_t alignment, size_t size);
void*		cudaGetParameterBufferV2				(void* func, dim3 gridDimension, dim3 blockDimension, unsigned int sharedMemSize);
#endif
