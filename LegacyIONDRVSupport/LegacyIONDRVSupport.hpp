/*
 * LegacyIONDRVSupport.hpp
 * LegacyIONDRVSupport
 *
 * Copyright (c) 2018 Linus. All rights reserved.
 */

#ifndef LegacyIONDRVSupport_hpp
#define LegacyIONDRVSupport_hpp

#include <IOKit/IOService.h>
#include <IOKit/ndrvsupport/IONDRVLibraries.h>
#include <Availability.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef ResType VSLGestaltType;

OSStatus
VSLGestalt( VSLGestaltType selector, UInt32 * response );

IOReturn IOGetHardwareClamshellState( IOOptionBits * result );
    
#ifdef __cplusplus
}
#endif

#define XSTR(a) STR(a)
#define STR(a) #a

#ifdef __MAC_10_12
#include <os/log.h>
// Simple wrapper for new os_log API, available in macOS 10.12 SDK and later
#define ilog(fmt, args...) os_log_with_type(OS_LOG_DEFAULT, OS_LOG_TYPE_DEFAULT, XSTR(PRODUCT_NAME) ": " fmt, ##args)
#define ilog_fault(fmt, args...) os_log_with_type(OS_LOG_DEFAULT, OS_LOG_TYPE_FAULT, XSTR(PRODUCT_NAME) ": " fmt, ##args)
#define ilog_error(fmt, args...) os_log_with_type(OS_LOG_DEFAULT, OS_LOG_TYPE_ERROR, XSTR(PRODUCT_NAME) ": " fmt, ##args)
#define ilog_debug(fmt, args...) os_log_with_type(OS_LOG_DEFAULT, OS_LOG_TYPE_DEBUG, XSTR(PRODUCT_NAME) ": " fmt, ##args)
#define ilog_info(fmt, args...) os_log_with_type(OS_LOG_DEFAULT, OS_LOG_TYPE_INFO, XSTR(PRODUCT_NAME) ": " fmt, ##args)
#else
// Use IOLog for earlier SDK compatibility
#include <IOKit/IOLib.h>
#define ilog(fmt, args...) IOLog( XSTR(PRODUCT_NAME) ": [INFO] " fmt "\n", ##args )
#define ilog_fault(fmt, args...) IOLog( XSTR(PRODUCT_NAME) ": [FAULT] " fmt "\n", ##args )
#define ilog_error(fmt, args...) IOLog( XSTR(PRODUCT_NAME) ": [ERROR] " fmt "\n", ##args )
#define ilog_debug(fmt, args...) IOLog( XSTR(PRODUCT_NAME) ": [DEBUG] " fmt "\n", ##args )
#define ilog_debug(fmt, args...) IOLog( XSTR(PRODUCT_NAME) ": [INFO] " fmt "\n", ##args )
#endif // __MAC_10_12

class PRODUCT_NAME : public IOService
{
    OSDeclareDefaultStructors(PRODUCT_NAME)
public:
    virtual bool init(OSDictionary *dictionary = 0) override;
    virtual void free(void) override;
    virtual IOService *probe(IOService *provider, SInt32 *score) override;
    virtual bool start(IOService *provider) override;
    virtual void stop(IOService *provider) override;
};

#endif /* LegacyIONDRVSupport_hpp */
