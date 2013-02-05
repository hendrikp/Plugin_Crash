/* Crash_Plugin - for licensing and copyright see license.txt */

#include <StdAfx.h>

#include <CPluginCrash.h>
#include <Nodes/G2FlowBaseNode.h>

namespace CrashPlugin
{
    class CFlowCrashNode :
        public CFlowBaseNode<eNCT_Instanced>
    {
            enum EInputPorts
            {
                EIP_CRASH = 0,
            };

        public:
            virtual void GetMemoryUsage( ICrySizer* s ) const
            {
                s->Add( *this );
            }

            virtual IFlowNodePtr Clone( SActivationInfo* pActInfo )
            {
                return new CFlowCrashNode( pActInfo );
            }

            CFlowCrashNode( SActivationInfo* pActInfo )
            {

            }

            virtual void GetConfiguration( SFlowNodeConfig& config )
            {
                static const SInputPortConfig inputs[] =
                {
                    InputPortConfig_Void( "Crash", _HELP( "Crash Game" ) ),
                    InputPortConfig_Null(),
                };

                config.pInputPorts = inputs;
                config.pOutputPorts = NULL;
                config.sDescription = _HELP( " Crash Game" );

                config.SetCategory( EFLN_APPROVED );
            }

            virtual void ProcessEvent( EFlowEvent evt, SActivationInfo* pActInfo )
            {
                switch ( evt )
                {
                    case eFE_Activate:

                        if ( IsPortActive( pActInfo, EIP_CRASH ) )
                        {
                            gPlugin->Crash();
                        }

                        break;
                }
            }
    };
}

REGISTER_FLOW_NODE_EX( "Crash_Plugin:Crash",  CrashPlugin::CFlowCrashNode, CFlowCrashNode );
