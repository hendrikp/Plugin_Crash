/* Crash_Plugin - for licensing and copyright see license.txt */

#pragma once

#include <Game.h>
#include <map>

#include <IPluginManager.h>
#include <IPluginBase.h>
#include <CPluginBase.hpp>

#include <IPluginCrash.h>

#define PLUGIN_NAME "Crash"
#define PLUGIN_CONSOLE_PREFIX "[" PLUGIN_NAME " " PLUGIN_TEXT "] " //!< Prefix for Logentries by this plugin
#define PLUGIN_FILENAME TEXT(PLUGIN_TEXT "_" PLUGIN_NAME CrySharedLibrayExtension) //!< Filename of the Plugin

#define PLUGIN_PATH PLUGIN_FOLDER "\\" PLUGIN_FILENAME //!< Full Path of the plugin

namespace CrashPlugin
{
    /**
    * @brief List All Plugins
    * Console CVar Command
    * Usage: pm_list
    */
    void Command_Crash( IConsoleCmdArgs* pArgs );

    /**
    * @brief Plugin Manager manages the plugin resources
    */
    class CPluginCrash :
        public PluginManager::CPluginBase,
        public IPluginCrash
    {
        public:
            CPluginCrash();
            ~CPluginCrash();

            // IPluginBase
            void Release();

            int GetInitializationMode() const
            {
                return int( PluginManager::IM_Default );
            };

            bool Check( const char* sAPIVersion ) const;

            bool Init( SSystemGlobalEnvironment& env, SSystemInitParams& startupParams, IPluginBase* pPluginManager );

            const char* GetVersion() const
            {
                return "1.0";
            };

            const char* GetName() const
            {
                return "Crash";
            };

            const char* GetCategory() const
            {
                return "General";
            };

            const char* ListAuthors() const
            {
                return "Hendrik \"hendrikp\" Polczynski";
            };

            const char* ListCVars() const;

            const char* GetStatus() const;

            const char* GetCurrentConcreteInterfaceVersion() const
            {
                return "1.0";
            };

            void* GetConcreteInterface( const char* sInterfaceVersion )
            {
                return static_cast<IPluginCrash*>( this );
            };

            // IPluginCrash
            void Crash();

            IPluginBase* GetBase()
            {
                return static_cast<IPluginBase*>( this );
            };
    };

    extern CPluginCrash* gPlugin;
}