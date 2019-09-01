#include "SWRCEditorModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"

IMPLEMENT_GAME_MODULE(FSWRCEditorModuleInterface, SWRCEditor);

DEFINE_LOG_CATEGORY(SWRCEditorLog)

#define LOCTEXT_NAMESPACE "SWRCEditor"

void FSWRCEditorModuleInterface::StartupModule()
{
	UE_LOG(SWRCEditorLog, Warning, TEXT("SWRCEditor: Log Started"));
}

void FSWRCEditorModuleInterface::ShutdownModule()
{
	UE_LOG(SWRCEditorLog, Warning, TEXT("SWRCEditor: Log Ended"));
}

#undef LOCTEXT_NAMESPACE