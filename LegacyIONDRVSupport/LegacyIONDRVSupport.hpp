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
#include <os/log.h>

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

#define ilog(fmt, args...) os_log_with_type(OS_LOG_DEFAULT, OS_LOG_TYPE_DEFAULT, XSTR(PRODUCT_NAME) ": " fmt, ##args)
#define ilog_fault(fmt, args...) os_log_with_type(OS_LOG_DEFAULT, OS_LOG_TYPE_FAULT, XSTR(PRODUCT_NAME) ": " fmt, ##args)
#define ilog_error(fmt, args...) os_log_with_type(OS_LOG_DEFAULT, OS_LOG_TYPE_ERROR, XSTR(PRODUCT_NAME) ": " fmt, ##args)
#define ilog_debug(fmt, args...) os_log_with_type(OS_LOG_DEFAULT, OS_LOG_TYPE_DEBUG, XSTR(PRODUCT_NAME) ": " fmt, ##args)
#define ilog_info(fmt, args...) os_log_with_type(OS_LOG_DEFAULT, OS_LOG_TYPE_INFO, XSTR(PRODUCT_NAME) ": " fmt, ##args)

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
