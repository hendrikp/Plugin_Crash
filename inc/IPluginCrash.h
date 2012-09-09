/* Crash_Plugin - for licensing and copyright see license.txt */

#include <IPluginBase.h>

#pragma once

/**
* @brief Crash Plugin Namespace
*/
namespace CrashPlugin
{
    /**
    * @brief plugin manager interface
    */
    struct IPluginCrash
    {
        /**
        * @brief Get PluginManager base interface
        */
        virtual PluginManager::IPluginBase* GetBase() = 0;

        /**
        * @brief Crash the process
        */
        virtual void Crash() = 0;
    };
};