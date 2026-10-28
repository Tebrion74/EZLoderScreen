// EZ "sticky hands": harmless, funny cousin of bloody hands (from slicing pineapples).
// No damage, no sickness, no stat effects. Not persisted across relog (by design, see README note).
modded class PlayerBase
{
	bool m_EZStickyHands;
	bool m_EZFakeBloodyForWash; // only true while a wash action re-checks its vanilla condition

	static const int EZ_STICKY_MIN_MS = 90000;
	static const int EZ_STICKY_MAX_MS = 150000;

	void PlayerBase()
	{
		RegisterNetSyncVariableBool("m_EZStickyHands");
	}

	bool EZ_HasStickyHands()
	{
		return m_EZStickyHands;
	}

	// lets the vanilla wash-hands ActionCondition pass for sticky-only hands (gloves etc. still checked by vanilla)
	override bool HasBloodyHands()
	{
		if (m_EZFakeBloodyForWash)
			return true;
		return super.HasBloodyHands();
	}

	void EZ_Notify(string text)
	{
		if (!GetGame().IsServer())
			return;
		NotificationSystem.SendNotificationToPlayerExtended(this, 6, "Sticky hands", text, "set:dayz_gui image:icon_info");
	}

	void EZ_SetStickyHands(bool state)
	{
		if (!GetGame().IsServer())
			return;
		bool was = m_EZStickyHands;
		m_EZStickyHands = state;
		SetSynchDirty();
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(EZ_StickyTick);
		if (state)
		{
			if (!was)
				EZ_Notify("Your hands are sticky with pineapple juice.");
			EZ_ScheduleStickyTick();
		}
		else if (was)
		{
			EZ_Notify("Your hands are clean. Sweet relief.");
		}
	}

	void EZ_ScheduleStickyTick()
	{
		int delay = Math.RandomIntInclusive(EZ_STICKY_MIN_MS, EZ_STICKY_MAX_MS);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(EZ_StickyTick, delay, false);
	}

	void EZ_StickyTick()
	{
		if (!m_EZStickyHands || !IsAlive())
			return;
		array<string> lines = {
			"Your hands are sticky with pineapple juice.",
			"Everything you touch is now slightly sticky.",
			"You smell faintly tropical.",
			"Your fingers keep sticking together. Wash your hands."
		};
		EZ_Notify(lines.GetRandomElement());
		EZ_ScheduleStickyTick();
	}

	override void EEKilled(Object killer)
	{
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(EZ_StickyTick);
		super.EEKilled(killer);
	}

	void ~PlayerBase()
	{
		if (GetGame())
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(EZ_StickyTick);
	}
}
