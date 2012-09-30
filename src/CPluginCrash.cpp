/* Crash_Plugin - for licensing and copyright see license.txt */

#include <StdAfx.h>
#include <CPluginCrash.h>

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
        gPlugin = NULL;
    }

    bool CPluginCrash::Release( bool bForce )
    {
        // Should be called while Game is still active otherwise there might be leaks/problems
        bool bRet = CPluginBase::Release( bForce );

        if ( bRet )
        {
            // Depending on your plugin you might not want to unregister anything
            // if the System is quitting.
            // if(gEnv && gEnv->pSystem && !gEnv->pSystem->IsQuitting()) {

            // Unregister CVars
            if ( gEnv && gEnv->pConsole )
            {
                gEnv->pConsole->RemoveCommand( "pc_crash" );
            }

            // Unregister game objects
            if ( gEnv && gEnv->pGameFramework )
            {
                // ...
            }

            // Cleanup like this always (since the class is static its cleaned up when the dll is unloaded)
            gPluginManager->UnloadPlugin( GetName() );
            m_bCanUnload = true;
        }

        return bRet;
    };

    bool CPluginCrash::Init( SSystemGlobalEnvironment& env, SSystemInitParams& startupParams, IPluginBase* pPluginManager )
    {
        gPluginManager = ( PluginManager::IPluginManager* )pPluginManager->GetConcreteInterface( NULL );
        bool bRet = CPluginBase::Init( env, startupParams, pPluginManager );

        if ( bRet )
        {
            // ... Do initializations needed by other plugins
        }

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
                gEnv->pConsole->AddCommand( "pc_crash", Command_Crash, VF_NULL, "Crash the process" );
            }

            // Register Game Objects
            // ...
        }

        return bRet;
    }

    const char* CPluginCrash::ListCVars() const
    {
        return "pc_crash,\n";
    }

    bool CPluginCrash::Check( const char* sAPIVersion ) const
    {
        if ( !sAPIVersion )
        {
            return false;
        }

        if ( SFileVersion( sAPIVersion ) == SFileVersion( "3.4.0" ) )
        {
            return true;
        }

        return false;
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