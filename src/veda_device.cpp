#include "veda/veda.hpp"
#include <productinfo.h>

extern "C" {
// implementation of VEDA API functions
/**
 * \defgroup vedaapi VEDA API
 *
 * To use VEDA API functions, include "veda.h" header.
 */
/** @{ */
//------------------------------------------------------------------------------
/**
 * @brief Retrieve the VEDA Context bound to the VEDA device.
 * @param ctx VEDA Context handle.
 * @param device VEDA device ID.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 */
VEDAresult	vedaCtxGet			(VEDAcontext* ctx, const VEDAdevice device)		{	GUARDED(*ctx = veda::Devices::get(device).ctx();)		}
//------------------------------------------------------------------------------
/**
 * @brief Retrieve the core temperature of the VEDA device in Celsius.
 * @param tempC pointer to hold the core temperature.
 * @param coreIdx Core index of the VEDA device.
 * @param dev VEDA device ID.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 */
VEDAresult	vedaDeviceGetTemp		(float* tempC, const int coreIdx, VEDAdevice dev)	{	GUARDED(*tempC = veda::Devices::get(dev).coreTemp(coreIdx);)	}
//------------------------------------------------------------------------------
/**
 * @brief Retrieve the number of initializaed VEDA device.
 * @param count pointer to hold the count of the VEDA device.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 */
VEDAresult	vedaDeviceGetCount		(int* count)						{	GUARDED(*count = veda::Devices::count();)			}
//------------------------------------------------------------------------------
/**
 * @brief Retrieve the total memory of the VEDA device in bytes.
 * @param bytes pointer to hold the VEDA device memory.
 * @param dev VEDA device ID.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 */
VEDAresult	vedaDeviceTotalMem		(size_t* bytes, VEDAdevice dev)				{	GUARDED(*bytes = veda::Devices::get(dev).memorySize();)		}
//------------------------------------------------------------------------------
/**
 * @brief This function is not yet implemented. 
 * @param dev
 * @return VEDA_SUCCESS\n 
 *
 * This function is not yet implemented but return VEDA_SUCCESS while calling it.
 */
VEDAresult	vedaDevicePrimaryCtxRelease	(VEDAdevice dev)					{	return VEDA_SUCCESS;						}
//------------------------------------------------------------------------------
/**
 * @brief This function is not yet implemented. 
 * @param dev
 * @param flags
 * @return VEDA_SUCCESS\n 
 *
 * This function is not yet implemented but return VEDA_SUCCESS while calling it.
 */
VEDAresult	vedaDevicePrimaryCtxSetFlags	(VEDAdevice dev, uint32_t flags)			{	return VEDA_SUCCESS;						}
//------------------------------------------------------------------------------
/**
 * @brief Retrieve the Physical ID  of the given VEDA device.
 * @param id pointer to hold the physical id of the VEDA device
 * @param dev VEDA device ID.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.\n 
 *
 * Physical ID is the Slot ID of the underlying VE node, physical ID is used 
 * internally to retrieve the VE node information like VE node temperature, 
 * voltage etc. from the VE device file.
 */
VEDAresult	vedaDeviceGetPhysicalId		(int* id, VEDAdevice dev)				{	GUARDED(*id = veda::Devices::get(dev).sensorId();)		}
//------------------------------------------------------------------------------
/**
 * @brief Retrieve the AVEO ID  of the given VEDA device.
 * @param id pointer to hold the AVEO id of the VEDA device
 * @param dev VEDA device ID.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.\n 
 *
 * AVEO ID is the logical node ID of the underlying VE node assigned by the VEOS
 * at the time of the VE node initialization.
 */
VEDAresult	vedaDeviceGetAVEOId		(int* id, VEDAdevice dev)				{	GUARDED(*id = veda::Devices::get(dev).aveoId();)		}
//------------------------------------------------------------------------------
/**
 * @brief Retrieve the NUMA ID of the given VEDA device.
 * @param id pointer to hold the NUMA id of the VEDA device
 * @param dev VEDA device ID.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.\n 
 *
 * if VE device is not configured in NUMA mode then this ID will be 0..
 */
VEDAresult	vedaDeviceGetNUMAId		(int* id, VEDAdevice dev)				{	GUARDED(*id = veda::Devices::get(dev).numaId();)		}

//------------------------------------------------------------------------------
/**
 * @brief Retrieve the distance of the two given VEDA devices.
 * @param distance pointer to hold the distance.
 * @param devA handle to the first VEDA device.
 * @param devB handle to the second VEDA device.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.\n 
 *
 * Returns following value of distances:\n 
 * 0: if both the VEDA devices are initialized on the same VE device.\n 
 * 0.5: if both the VEDA devices are initialized on the difference NUMA node of 
 * the same VE device.\n 
 * 1: if both the VEDA devices are initialized on the difference VE node. \n 
 */
VEDAresult vedaDeviceDistance(float* distance, VEDAdevice devA, VEDAdevice devB) {
	GUARDED(
		*distance = 0.0f;

		auto& A = veda::Devices::get(devA);
		auto& B = veda::Devices::get(devB);
		
		if(A.vedaId() == B.vedaId()) {
			*distance = 0.0f;
		} else if(A.aveoId() == B.aveoId()) {
			ASSERT(A.numaId() != B.numaId());
			*distance = 0.5f;
		} else {
			*distance = 1.0f;
		}
	)
}

//------------------------------------------------------------------------------
/**
 * @brief Returns a handle to compute VEDA Device.
 * @param device pointer to hold the VEDA device handle.
 * @param ordinal VEDA device number to get the VEDA device handle.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 */
VEDAresult vedaDeviceGet(VEDAdevice* device, int ordinal) {
	GUARDED(
		veda::Devices::get(ordinal);
		*device = ordinal;
	)
}

//------------------------------------------------------------------------------
/**
 * @brief Returns a VE device power corresponding to VEDA Device.
 * @param watts pointer to hold the VE device power.
 * @param dev VEDA device handle.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.\n 
 *
 * Calculated VE device power includes both the PCIe edge power as well as the VE
 * device AUX power with added 5W.
 */
VEDAresult vedaDeviceGetPower(float* watts, VEDAdevice dev) {
	GUARDED(
		auto& device = veda::Devices::get(dev);
		*watts = ((device.powerVoltage() * device.powerCurrent())+(device.powerVoltageEdge() * device.powerCurrentEdge())+5.0);
	)
}

//------------------------------------------------------------------------------
/**
 * @brief Returns a VE device AUX current corresponding to VEDA Device.
 * @param current pointer to hold the VE device voltage.
 * @param dev VEDA device handle.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 */
VEDAresult vedaDeviceGetCurrent(float* current, VEDAdevice dev) { GUARDED(*current = veda::Devices::get(dev).powerCurrent();)	}

//------------------------------------------------------------------------------
/**
 * @brief Returns a VE device PCIe edge current corresponding to VEDA Device.
 * @param current pointer to hold the VE device current.
 * @param dev VEDA device handle.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 */
VEDAresult vedaDeviceGetCurrentEdge(float* current, VEDAdevice dev) {
	GUARDED(
		if(NULL == current)
			throw VEDA_ERROR_INVALID_ARGS;
		*current = veda::Devices::get(dev).powerCurrentEdge();
	)
}

//------------------------------------------------------------------------------
/**
 * @brief Returns a VE device AUX voltage corresponding to VEDA Device.
 * @param voltage pointer to hold the VE device voltage.
 * @param dev VEDA device handle.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 */
VEDAresult vedaDeviceGetVoltage(float* voltage, VEDAdevice dev) { GUARDED(*voltage = veda::Devices::get(dev).powerVoltage();)	}

//------------------------------------------------------------------------------
/**
 * @brief Returns a VE device PCIe edge voltage corresponding to VEDA Device.
 * @param voltage pointer to hold the VE device voltage.
 * @param dev VEDA device handle.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 */
VEDAresult vedaDeviceGetVoltageEdge(float* voltage, VEDAdevice dev) {
	GUARDED(
		if(NULL == voltage)
			throw VEDA_ERROR_INVALID_ARGS;
		*voltage = veda::Devices::get(dev).powerVoltageEdge();
	)
}

//------------------------------------------------------------------------------
/**
 * @brief Returns information about the VEDA device.
 * @param pi Returned VEDA device attribute value.
 * @param attrib VEDA Device attribute to query.
 * @param dev VEDA device handle.
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
 * VEDA device.\n 
 */
VEDAresult vedaDeviceGetAttribute(int* pi, VEDAdevice_attribute attrib, VEDAdevice dev) {
	GUARDED(
		if(attrib == VEDA_DEVICE_ATTRIBUTE_SINGLE_TO_DOUBLE_PRECISION_PERF_RATIO) {
			*pi = 2;
		} else {
			auto& device = veda::Devices::get(dev);
			*pi = [&](void) -> int {
				switch(attrib) {
					case VEDA_DEVICE_ATTRIBUTE_CLOCK_RATE:			return device.clockRate();
					case VEDA_DEVICE_ATTRIBUTE_CLOCK_BASE:			return device.clockBase();
					case VEDA_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT:	return device.cores();
					case VEDA_DEVICE_ATTRIBUTE_MEMORY_CLOCK_RATE:		return device.clockMemory();
					case VEDA_DEVICE_ATTRIBUTE_L1D_CACHE_SIZE:		return device.cacheL1d();
					case VEDA_DEVICE_ATTRIBUTE_L1I_CACHE_SIZE:		return device.cacheL1i();
					case VEDA_DEVICE_ATTRIBUTE_L2_CACHE_SIZE:		return device.cacheL2();
					case VEDA_DEVICE_ATTRIBUTE_LLC_CACHE_SIZE:		return device.cacheLLC();
					case VEDA_DEVICE_ATTRIBUTE_MODEL:			return device.model();
					case VEDA_DEVICE_ATTRIBUTE_ABI_VERSION:			return device.versionAbi();
					case VEDA_DEVICE_ATTRIBUTE_FIREWARE_VERSION:		return device.versionFirmware();
				}

				throw VEDA_ERROR_UNKNOWN_ATTRIBUTE;
				return 0;
			}();
		}
	)
}

//------------------------------------------------------------------------------
/**
 * @brief Returns an identifer string for the VEDA device.
 * @param name Returned identifier string for the VEDA device.
 * @param len Maximum length of string to store in name.
 * @param dev Device to get the identifier string
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.\n 
 *
 * Returns an ASCII string identifying the device dev in the NULL-terminated 
 * string pointed to by name. len specifies the maximum length of the string that
 * may be returned.
 */
VEDAresult vedaDeviceGetName(char* name, int len, VEDAdevice dev) {
	GUARDED(
		auto& device = veda::Devices::get(dev);
		auto version		= device.model();
		auto type		= device.type();
		char model[20];  
		memset(model, '\0', sizeof(model));
		std::string ver = std::to_string(version);
		std::string typ = std::to_string(type);
  		char* v = const_cast<char*>(ver.c_str());
  		char* t = const_cast<char*>(typ.c_str());

		/* Get the model name from VE specific sysfs*/
	        int retval = get_ve_product_name(v, t, model, sizeof(model));
        	if (retval != 0)
			strcpy(model," Unknown Model");
		snprintf(name, len, "NEC SX-Aurora Tsubasa VE%s", model);
	)
}

//------------------------------------------------------------------------------
/**
 * @brief Get the state of the primary context.
 * @param dev VEDA Device to get the primary context flags for.
 * @param flags Pointer to store flags
 * @param active Pointer to store context state; 0 = inactive, 1 = active.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 */
VEDAresult vedaDevicePrimaryCtxGetState(VEDAdevice dev, uint32_t* flags, int* active) {
	GUARDED(
		*flags	= 0;
		*active = veda::Devices::get(dev).unsafeCtx() != 0;
	)
}

//------------------------------------------------------------------------------
/**
 * @brief Destroy all allocations and reset all state on the primary context.
 * @param dev VEDA Device for which primary context is destroyed.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 * @retval VEDA_ERROR_CANNOT_CREATE_CONTEXT Error while creating VEDA context.
 * @retval VEDA_ERROR_CANNOT_CREATE_STREAM error while creating VEDA SM.
 *
 * Explicitly destroys and cleans up all resources associated with the current
 * device in the current process.
 */
VEDAresult vedaDevicePrimaryCtxReset(VEDAdevice dev) {
	GUARDED(
		auto& device = veda::Devices::get(dev);
		if(auto ctx = device.unsafeCtx()) {
			auto mode = ctx->mode();
			device.destroyCtx();
			device.createCtx(mode);
		}
	)
}

//------------------------------------------------------------------------------
/**
 * @brief Retain the primary Context on the VEDA device.
 * @param pctx Returned context handle of the new VEDA context.
 * @param dev VEDA Device for which primary context is released.
 * @retval VEDA_SUCCESS on Success
 * @retval VEDA_ERROR_NOT_INITIALIZED VEDA library not initialized
 * @retval VEDA_ERROR_INVALID_DEVICE VEDA device id is not valid.
 * @retval VEDA_ERROR_CANNOT_CREATE_CONTEXT Error while creating VEDA context.
 * @retval VEDA_ERROR_CANNOT_CREATE_STREAM error while creating VEDA SM.
 *
 * Retains the primary context on the device. Once the user successfully
 * retains the primary context, the primary context will be active and available
 * to the user until the user resets it with vedaDevicePrimaryCtxReset(). 
 * Unlike vedaCtxCreate() the newly retained context is not pushed onto the stack.
 */
VEDAresult vedaDevicePrimaryCtxRetain(VEDAcontext* pctx, VEDAdevice dev) {
	GUARDED(
		auto& device = veda::Devices::get(dev);
		if(!device.unsafeCtx())
			device.createCtx(VEDA_CONTEXT_MODE_OMP);
		*pctx = device.ctx();
	)
}
/** @} */
//------------------------------------------------------------------------------
} // extern "C"
