// EchelonZ: bigger Expansion chat box + reliable line wrapping.
// Requires DayZExpansion_Chat_Scripts / DayZExpansion_Chat_GUI in requiredAddons.
#ifdef EXPANSIONMODCHAT
modded class ExpansionChatUIWindow
{
	override string GetLayoutFile()
	{
		return "EZLoderScreen/gui/layouts/ez_expansion_chat.layout";
	}
}

modded class ExpansionChatLineBase
{
	override void Set(ExpansionChatMessage message)
	{
		super.Set(message);
		// Time/SenderName use "size to text"; their new width is only known after a layout pass,
		// so Expansion's own width calc can use stale sizes and clip the message. Redo it next frame.
		if (message)
		{
			g_Game.GetCallQueue(CALL_CATEGORY_GUI).Remove(EZ_FixMessageWidth);
			g_Game.GetCallQueue(CALL_CATEGORY_GUI).CallLater(EZ_FixMessageWidth, 1, false);
		}
	}

	void EZ_FixMessageWidth()
	{
		Widget root = GetLayoutRoot();
		if (!root || !root.GetParent())
			return;

		Widget timeW = root.FindAnyWidget("Time");
		Widget senderW = root.FindAnyWidget("SenderName");
		Widget msgW = root.FindAnyWidget("Message");
		if (!timeW || !senderW || !msgW)
			return;

		float root_w, root_h, time_w, time_h, sender_w, sender_h;
		root.GetParent().GetScreenSize(root_w, root_h);
		if (root_w <= 0)
			return;
		timeW.GetScreenSize(time_w, time_h);
		senderW.GetScreenSize(sender_w, sender_h);

		// 24px safety margin for the left-side scrollbar
		float frac = 1.0 - (time_w + sender_w + 24) / root_w;
		if (frac < 0.3)
			frac = 0.3;
		msgW.SetSize(frac, 1.0);
	}
}
#endif
