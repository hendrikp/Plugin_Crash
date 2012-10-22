/* Crash_Plugin - for licensing and copyright see license.txt */

#include <StdAfx.h>
#include <CPluginCrash.h>

#define COMMAND_CRASH "pc_crash"

namespace CrashPlugin
{
    CPluginCrash* gPlugin = NULL;

    void Command_Crash( IConsoleCmdArgs* pArgs )
    {
        if ( !gPlugin )
        {
            return;
        }

        gPlugin->Crash();
    };

    CPluginCrash::CPluginCrash()
    {
        gPlugin = this;
    }

    CPluginCrash::~CPluginCrash()
    {
        Release( true );

        gPlugin = NULL;
    }

    bool CPluginCrash::Release( bool bForce )
    {
        bool bRet = true;

        if ( !m_bCanUnload )
        {
            // Should be called while Game is still active otherwise there might be leaks/problems
            bRet = CPluginBase::Release( bForce );

            if ( bRet )
            {
                // Unregister CVars
                if ( gEnv && gEnv->pConsole )
                {
                    gEnv->pConsole->RemoveCommand( COMMAND_CRASH );
                }

                // Cleanup like this always (since the class is static its cleaned up when the dll is unloaded)
                gPluginManager->UnloadPlugin( GetName() );

                // Allow Plugin Manager garbage collector to unload this plugin
                AllowDllUnload();
            }
        }

        return bRet;
    };

    bool CPluginCrash::Init( SSystemGlobalEnvironment& env, SSystemInitParams& startupParams, IPluginBase* pPluginManager, const char* sPluginDirectory )
    {
        gPluginManager = ( PluginManager::IPluginManager* )pPluginManager->GetConcreteInterface( NULL );
        bool bRet = CPluginBase::Init( env, startupParams, pPluginManager, sPluginDirectory );

        return bRet;
    }

    bool CPluginCrash::InitDependencies()
    {
        bool bRet = CPluginBase::InitDependencies(  );

        if ( bRet )
        {
            // Register CVars
            if ( gEnv && gEnv->pConsole )
            {
                gEnv->pConsole->AddCommand( COMMAND_CRASH, Command_Crash, VF_NULL, "Crash the process" );
            }
        }

        return bRet;
    }

    const char* CPluginCrash::ListCVars() const
    {
        return COMMAND_CRASH ",\n";
    }

    const char* CPluginCrash::GetStatus() const
    {
        return "OK";
    }

    void CPluginCrash::Crash()
    {
        // Memory violation
        *( reinterpret_cast<int*>( 0xbaadf00d ) ) = 0xbaadf00d;
        *( reinterpret_cast<int*>( 0xdeadbeef ) ) = 0xdeadbeef;

        // Make sure using Stackoverflow
        Crash();
    }
}