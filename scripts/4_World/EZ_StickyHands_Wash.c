// EZ sticky hands: vanilla wash-hands actions also accept and clear sticky hands.
modded class ActionWashHandsWater
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (super.ActionCondition(player, target, item))
			return true;
		if (!player || !player.EZ_HasStickyHands())
			return false;
		// re-run the vanilla checks (gloves, water, item...) pretending hands are bloody
		player.m_EZFakeBloodyForWash = true;
		bool ok = super.ActionCondition(player, target, item);
		player.m_EZFakeBloodyForWash = false;
		return ok;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		super.OnFinishProgressServer(action_data);
		if (action_data && action_data.m_Player)
			action_data.m_Player.EZ_SetStickyHands(false);
	}
}

modded class ActionWashHandsWell
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (super.ActionCondition(player, target, item))
			return true;
		if (!player || !player.EZ_HasStickyHands())
			return false;
		// re-run the vanilla checks (gloves, water, item...) pretending hands are bloody
		player.m_EZFakeBloodyForWash = true;
		bool ok = super.ActionCondition(player, target, item);
		player.m_EZFakeBloodyForWash = false;
		return ok;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		super.OnFinishProgressServer(action_data);
		if (action_data && action_data.m_Player)
			action_data.m_Player.EZ_SetStickyHands(false);
	}
}

modded class ActionWashHandsItemContinuous
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (super.ActionCondition(player, target, item))
			return true;
		if (!player || !player.EZ_HasStickyHands())
			return false;
		// re-run the vanilla checks (gloves, water, item...) pretending hands are bloody
		player.m_EZFakeBloodyForWash = true;
		bool ok = super.ActionCondition(player, target, item);
		player.m_EZFakeBloodyForWash = false;
		return ok;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		super.OnFinishProgressServer(action_data);
		if (action_data && action_data.m_Player)
			action_data.m_Player.EZ_SetStickyHands(false);
	}
}

modded class ActionWashHandsItem
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (super.ActionCondition(player, target, item))
			return true;
		if (!player || !player.EZ_HasStickyHands())
			return false;
		// re-run the vanilla checks (gloves, water, item...) pretending hands are bloody
		player.m_EZFakeBloodyForWash = true;
		bool ok = super.ActionCondition(player, target, item);
		player.m_EZFakeBloodyForWash = false;
		return ok;
	}

	override void OnExecuteServer(ActionData action_data)
	{
		super.OnExecuteServer(action_data);
		if (action_data && action_data.m_Player)
			action_data.m_Player.EZ_SetStickyHands(false);
	}
}

