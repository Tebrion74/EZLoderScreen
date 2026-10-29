// EZ Terje Field Medical Manual: item + "Read manual" action (client opens EZMedManualMenu, 5_Mission).
// Menu id lives here (4_World) so the action can open it; the menu class itself is in 5_Mission.
const int EZ_MENU_MEDMANUAL = 82341101;

class EZ_TerjeMedManual extends ItemBase
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionReadMedManual);
	}
}

class ActionReadMedManual : ActionSingleUseBase
{
	void ActionReadMedManual()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_ITEM_ON;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONFB_ITEM_ON;
		m_Text = "Read manual";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

	override bool HasTarget()
	{
		return false;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return item && item.IsInherited(EZ_TerjeMedManual);
	}

	// nothing happens server-side; reading is purely client UI
	override protected void OnExecuteServer(ActionData action_data)
	{
	}

	override protected void OnExecuteClient(ActionData action_data)
	{
		if (!GetGame() || GetGame().IsDedicatedServer())
			return;
		if (!action_data.m_Player || action_data.m_Player != GetGame().GetPlayer())
			return;
		UIManager ui = GetGame().GetUIManager();
		if (ui && !ui.GetMenu())
			ui.EnterScriptedMenu(EZ_MENU_MEDMANUAL, null);
	}
}

// Register the action so it is always available (vanilla pattern)
modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		actions.Insert(ActionReadMedManual);
	}
}
