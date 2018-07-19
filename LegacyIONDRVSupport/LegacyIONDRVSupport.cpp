/*
 * LegacyIONDRVSupport.cpp
 * LegacyIONDRVSupport
 *
 * Copyright (c) 2018 Linus. All rights reserved.
 */

#include "LegacyIONDRVSupport.hpp"
#include <libkern/version.h>

// This required macro defines the class's constructors, destructors,
// and several other methods I/O Kit requires.
OSDefineMetaClassAndStructors(PRODUCT_NAME, IOService)

// Define the driver's superclass.
#define super IOService

//#define EXP(s) _e ## s
#define EXP(s) s

/*! When true, clamshell machines with external display keep running with lid
 *  closed; otherwise, clamshell always sleeps system. */
static bool gIOFBDesktopModeAllowed = true;

extern IOOptionBits gIOFBCurrentClamshellState;

bool PRODUCT_NAME::init(OSDictionary *dict)
{
    if (!super::init(dict))
        return false;
    
    ilog("v%s Copyright 2018 Linus. All rights reserved.", XSTR(MODULE_VERSION));
    ilog("Build date/time: %s %s", __DATE__, __TIME__);
    
    // check os version, only 10.14 supported
    if (version_major < 18)
    {
        ilog_error("This kext only supports macOS 10.14.");
        return false;
    }
    
    return true;
}

void PRODUCT_NAME::free(void)
{
    super::free();
}

IOService *PRODUCT_NAME::probe(IOService *provider, SInt32 *score)
{
    IOService *result = super::probe(provider, score);
    return result;
}

bool PRODUCT_NAME::start(IOService *provider)
{
    if (!super::start(provider))
        return false;
    
    registerService();
    
    return true;
}

void PRODUCT_NAME::stop(IOService *provider)
{
    super::stop(provider);
}

// Referenced from IOGraphics-517.22
OSStatus EXP(VSLGestalt)( VSLGestaltType selector, UInt32 * response )
{
    IOReturn ret;
    
    if (!response)
        return (paramErr);
    
    *response = 0;
    
    switch (selector)
    {
        case kVSLClamshellStateGestaltType:
            ret = IOGetHardwareClamshellState(response);
            break;
        default:
            ret = gestaltUndefSelectorErr;
            break;
    }
    
    return (ret);
}

// Referenced from IOGraphics-517.22
namespace {
    IOReturn getHardwareClamshellState(IOOptionBits *resultP)
    {
        // zero -> lid open
        if (gIOFBDesktopModeAllowed)
            /*! Use current state instead as it could be imported from IOGraphicsFamily.kext
             *  It should be fine in most cases however not fully tested. */
            
//            *resultP = gIOFBLastClamshellState;
            *resultP = gIOFBCurrentClamshellState;
        else
            *resultP = 0;
        // gIOFBLastReadClamshellState = gIOFBLastClamshellState;
        
        //DEBG1("S", " %d\n", (int) *resultP);
        ilog_debug("Current clamshell state = %d", (int) *resultP);
        return kIOReturnSuccess;
    }
}; // namespace

// Referenced from IOGraphics-517.22
extern "C" IOReturn
IOGetHardwareClamshellState(IOOptionBits *resultP)
{
    // External API called
    bool err = getHardwareClamshellState(resultP);
//    IOG_KTRACE(DBG_IOG_CLAMSHELL, DBG_FUNC_NONE,
//               0, DBG_IOG_SOURCE_IOGETHWCLAMSHELL,
//               0, err, 0, *resultP, 0, 0);
    return err;
}
