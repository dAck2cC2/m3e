/*******************************************************************************
  Created by Jeremy on 2015-08-08.
  Copyright 2015. All rights reserved.
*******************************************************************************/

/*******************************************************************************
    INCLUDE
*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include "engine/CEngineFactory.h"

using namespace ENGINE;

/*******************************************************************************
    INTERNAL FUNCTION
*******************************************************************************/

static void usage(void);
//static void frontend_msgf(const char *format, va_list ap);

/*******************************************************************************
    DEFINITION
*******************************************************************************/

int main(int argc, char *argv[])
{
    //printf("MP3 Encoder version 0.1 \n");

    // argv[1] is path or wave file.
    if (argc != 2) {
        usage();
        return (-1);
    }

    sp<IEngineScanner>       pScanner = CEngineFactory::getInstance().createMediaScanner();
    sp<IEngineScannerClient> pClient  = CEngineFactory::getInstance().createMP3EncoderClient();

    pClient->init();
    pScanner->processDirectory(argv[1], pClient);

//	::sleep(1);

    return 0;
}

static void
usage(void)
{
    printf("usage: m3e file \n");
    printf("file - is a wave file or a path for wave file \n");
}

//static void
//frontend_msgf(const char *format, va_list ap)
//{
//}


