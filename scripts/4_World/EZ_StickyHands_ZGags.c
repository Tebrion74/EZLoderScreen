// The Big Bang Rebuild: more harmless sticky-hands gags. No damage, no stats, all cleared by washing hands.
// (File name starts with Z so it compiles after EZ_StickyHands_Player.c, whose methods it extends.)
modded class PlayerBase
{
	int m_EZStickyTicks;

	// gag-only lines respect the client's "sticky gag messages" option (core sticky/clean notices always show)
	void EZ_GagNotify(string text)
	{
		if (m_EZGagMsgs)
			EZ_Notify(text);
	}

	override void EZ_SetStickyHands(bool state)
	{
		if (GetGame().IsServer())
			m_EZStickyTicks = 0;
		super.EZ_SetStickyHands(state);
	}

	override void EZ_StickyTick()
	{
		bool sticky = m_EZStickyHands && IsAlive();
		super.EZ_StickyTick();
		if (!sticky || !GetGame().IsServer())
			return;
		m_EZStickyTicks++;

		// Ant parade: after being sticky for a while
		if (m_EZStickyTicks >= 3 && Math.RandomFloat01() < 0.35)
		{
			array<string> ants = {
				"A tiny parade of ants is marching up your sleeve.",
				"The ants have elected you their new queen.",
				"You are now a mobile ant buffet. Wash your hands."
			};
			EZ_GagNotify(ants.GetRandomElement());
		}

		// Sticky handshake: 20% to share it with a player standing within 2 m
		array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);
		foreach (Man m : players)
		{
			PlayerBase other = PlayerBase.Cast(m);
			if (!other || other == this || !other.IsAlive() || other.EZ_HasStickyHands())
				continue;
			if (vector.DistanceSq(other.GetPosition(), GetPosition()) > 4.0)
				continue;
			if (Math.RandomFloat01() < 0.20)
			{
				other.EZ_SetStickyHands(true);
				other.EZ_Notify("Someone gave you a sticky handshake. Ew. Pineapple.");
				EZ_GagNotify("You shared your sticky hands. Friendship is sticky.");
			}
		}
	}

	// Sticky fingers: picking things up while sticky
	override void EEItemIntoHands(EntityAI item)
	{
		super.EEItemIntoHands(item);
		if (!GetGame().IsServer() || !m_EZStickyHands || !item)
			return;
		if (Math.RandomFloat01() < 0.15)
		{
			array<string> fingers = {
				"It takes a second to peel your fingers off the " + item.GetDisplayName() + ".",
				"The " + item.GetDisplayName() + " is now officially sticky.",
				"*schlurp* - your hand unsticks from the " + item.GetDisplayName() + "."
			};
			EZ_GagNotify(fingers.GetRandomElement());
		}
	}
}

// Sticky trigger: firing with sticky hands
modded class Weapon_Base
{
	override void EEFired(int muzzleType, int mode, string ammoType)
	{
		super.EEFired(muzzleType, mode, ammoType);
		if (!GetGame().IsServer())
			return;
		PlayerBase p = PlayerBase.Cast(GetHierarchyRootPlayer());
		if (!p || !p.EZ_HasStickyHands())
			return;
		if (Math.RandomFloat01() < 0.10)
		{
			array<string> lines = {
				"Your trigger finger is sticky. Pew... *squelch*.",
				"The trigger stuck to your finger for a moment. Tropical recoil.",
				"Your gun now smells like a pina colada."
			};
			p.EZ_GagNotify(lines.GetRandomElement());
		}
	}
}
