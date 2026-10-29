// EZ Terje Field Medical Manual - client-side paged reader. Opened by ActionReadMedManual (4_World).
// Content is based on the TerjeMedicine wiki (github.com/TerjeBruoygard/TerjeMods, WIKI/en/Medicine).
class EZMedManualMenu : UIScriptedMenu
{
	protected ref array<string> m_Titles;
	protected ref array<string> m_Bodies;
	protected int m_Page;
	protected TextWidget m_PageTitle;
	protected MultilineTextWidget m_PageBody;
	protected TextWidget m_PageNum;

	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("EZLoderScreen/gui/layouts/ez_medmanual.layout");
		m_PageTitle = TextWidget.Cast(layoutRoot.FindAnyWidget("EZPageTitle"));
		m_PageBody = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("EZPageBody"));
		m_PageNum = TextWidget.Cast(layoutRoot.FindAnyWidget("EZPageNum"));
		m_Titles = new array<string>;
		m_Bodies = new array<string>;
		BuildPages();
		m_Page = 0;
		ShowPage();
		return layoutRoot;
	}

	override void OnShow()
	{
		super.OnShow();
		GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
		GetGame().GetUIManager().ShowUICursor(true);
	}

	override void OnHide()
	{
		super.OnHide();
		GetGame().GetMission().PlayerControlEnable(true);
		GetGame().GetUIManager().ShowUICursor(false);
	}

	override void Update(float timeslice)
	{
		super.Update(timeslice);
		if (GetUApi().GetInputByID(UAUIBack).LocalPress())
		{
			Close();
			return;
		}
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		string n = w.GetName();
		if (n == "EZBtn_Prev") { Turn(-1); return true; }
		if (n == "EZBtn_Next") { Turn(1); return true; }
		if (n == "EZBtn_Close") { Close(); return true; }
		return false;
	}

	protected void Turn(int dir)
	{
		int p = m_Page + dir;
		if (p < 0 || p >= m_Titles.Count())
			return;
		m_Page = p;
		ShowPage();
	}

	protected void ShowPage()
	{
		if (m_Titles.Count() == 0)
			return;
		if (m_PageTitle) m_PageTitle.SetText(m_Titles[m_Page]);
		if (m_PageBody) m_PageBody.SetText(m_Bodies[m_Page]);
		if (m_PageNum) m_PageNum.SetText((m_Page + 1).ToString() + " / " + m_Titles.Count().ToString());
	}

	protected void AddPage(string title, string body)
	{
		m_Titles.Insert(title);
		m_Bodies.Insert(body);
	}

	protected void BuildPages()
	{
		string s;

		s = "Check yourself first: your status icons tell you what is wrong. A stethoscope (TerjeStethoscope) lets you inspect yourself or another survivor in detail.\n\n";
		s += "Medicines come as tablets (early stages, prevention), ampoules (need a syringe) and injectors (fast, strongest). Each medicine has a LEVEL: it only treats a condition of that level or lower.\n\n";
		s += "Every dose adds to overdose. Do not stack drugs you do not need.\n\n";
		s += "Always disinfect hands and tools before treating open wounds.\n\nUse the Prev / Next buttons to turn pages. ESC closes.";
		AddPage("How to use this manual", s);

		s = "Symptoms: blood drops on screen, bleeding icon, falling blood level.\n\n";
		s += "Treat: bandage the wound.\n";
		s += "- Plaster (TerjePlaster): small cuts and scratches only.\n";
		s += "- Bandage / Rags: normal cuts.\n";
		s += "- Hemostatic Bandage (TerjeBandageHemostatic): strongest stop, also slows bleeding for several minutes.\n\n";
		s += "Use clean, disinfected dressings. Dirty rags and dirty hands risk sepsis.";
		AddPage("Bleeding: scratches and cuts", s);

		s = "Slow bleeding (hemostasis):\n- Vikasol tablets (TerjePillsVikasol), level 1\n- Erytromixelin injector (TerjeInjectorErytromixelin), level 3\n\n";
		s += "Restore blood (hematopoiesis):\n- Irovit (TerjePillsIrovit), Magnesium Sulfate (TerjePillsMagnesiumSulfate)\n- Erythropoetin ampoule / injector\n- Erytromixelin injector\n\n";
		s += "Also eat, drink and rest. Saline / blood transfusion still works.";
		AddPage("Hemorrhage and blood loss", s);

		s = "Symptoms: heavy bleeding after being shot or stabbed. After bandaging the wound keeps bleeding slightly until the bullet or blade fragment is removed by surgery.\n\n";
		s += "Step 1: Hemostatic bandage to control bleeding.\n";
		s += "Step 2: Surgery with Medical Bowl with Instrument (TerjeSurgicalTool_Ceramic / _White), Field Surgical Kit (TerjeSurgicalKit), IFAK or AFAK.\n";
		s += "Kits have limited uses and a chance to fail; better kits succeed more often.\n\n";
		s += "Armor: a vest that stops a bullet leaves a hematoma instead of a wound.";
		AddPage("Gunshot and stab wounds", s);

		s = "The most dangerous wound: deep bleeding that bandages alone will not fix.\n\n";
		s += "Treat with surgery. Success chance is low with a bowl and instrument, better with a Field Surgical Kit, best with IFAK / AFAK. Be ready to bandage again and repeat.\n\n";
		s += "Afterwards the stitches must be kept disinfected.";
		AddPage("Internal organ wounds", s);

		s = "Sutures left by surgery must be disinfected regularly or they will cause sepsis.\n\n";
		s += "Disinfect with Alcoholic Tincture (DisinfectantAlcohol) or Disinfectant Spray (DisinfectantSpray).\n\n";
		s += "Disinfect your hands, bandages and surgical tools before use. Dirty items are the main source of wound infection.";
		AddPage("Surgical sutures and disinfection", s);

		s = "Cause: infection entering an open wound - zombie scratches, knife or gunshot wounds, especially when treated with dirty hands.\n\n";
		s += "Symptoms: health slowly drops while the infection progresses.\n\n";
		s += "Treat (all level 3):\n- Flemoclav ampoule (TerjeAmpouleFlemoclav)\n- Imipenem ampoule (TerjeAmpouleImipenem)\n- Amoxiclav injector (TerjeInjectorAmoxiclav)\n- Topoisomerase injector (TerjeInjectorTopoizomeraza)";
		AddPage("Sepsis (wound infection)", s);

		s = "Cause: zombie hits, blunt weapons, or bullets stopped by armor.\n\n";
		s += "Symptoms: hematoma icon. Many bruises at once drain health.\n\n";
		s += "They heal on their own; ointments speed it up:\n- Viprosal (TerjeSalveViprosal)\n- Capsicum (TerjeSalveCapsicum)\n- Finalgon (TerjeSalveFinalgon)\n\nOintments carry no overdose.";
		AddPage("Hematomas (bruises)", s);

		s = "Cause: strong blow to the head, nearby explosion, or a small-caliber round stopped by a ballistic helmet.\n\n";
		s += "Symptoms: headache, dizziness, unsteady movement, blurred vision.\n\n";
		s += "Passes on its own; to speed recovery:\n- Noopept tablets (TerjePillsNoopept)\n- Neirox ampoule (TerjeAmpouleNeirox)\n- Neirox injector (TerjeInjectorNeirox)";
		AddPage("Concussion", s);

		s = "Symptoms: limping, cannot sprint, broken-bone icon. Caused by falls and heavy hits.\n\n";
		s += "Treat: apply a Splint (crafted from sticks + rags or bandage) and avoid running and jumping until it heals. Painkillers make moving bearable.\n\n";
		s += "(Fractures use the standard DayZ splint system; this manual has no Terje-specific fracture drug.)";
		AddPage("Fractures", s);

		s = "Pain follows every injury; strength depends on the trauma. It fades with time. A painkiller must be the SAME LEVEL OR HIGHER than the pain.\n\n";
		s += "Level 1: Analgin, Nimesulide, Paracetamol, Ibuprofen, Nurofen, Noopept, Ketarol ampoule.\n";
		s += "Level 2: Novacaine ampoule, Propital injector.\n";
		s += "Level 3: Morphine ampoule (TerjeAmpouleMorphine), Hexobarbital ampoule, Promidol injector, Reanimatal injector, vanilla Morphine auto-injector.";
		AddPage("Pain", s);

		s = "Cause: long exposure to cold. An untreated cold becomes pneumonia.\n\n";
		s += "Symptoms: sneezing, coughing, fever; pneumonia causes steady health loss.\n\n";
		s += "Level 1: Paracetamol, Amibaktam tablets.\n";
		s += "Level 2: Ibuprofen, Nurofen, Amoxiclav tablets, Piperacillin, Ketarol / Amoxivan ampoules.\n";
		s += "Level 3: Imipenem, Flemoclav ampoules, Topoisomerase or Amoxiclav injectors.\n";
		s += "Vaccine: Vaxicam (TerjeAmpouleVaxicam). Keep warm and sleep.";
		AddPage("Cold, flu and pneumonia", s);

		s = "Cause: spoiled, raw or rotten food, poisonous mushrooms, dirty water, gasoline.\n\n";
		s += "Symptoms: nausea and vomiting soon after eating; then dehydration and health loss.\n\n";
		s += "Drink plenty of clean water, then:\n";
		s += "Level 1: Polysorb (TerjePillsPolisorb), Phthalazole (TerjePillsFtalazol).\n";
		s += "Level 2: Mesalazine, Chelating Tablets, Metoclopramide ampoule.\n";
		s += "Level 3: Heptral ampoule, Stomaproxidal injector.";
		AddPage("Food poisoning", s);

		s = "Cause: breathing toxic gas.\n\n";
		s += "Symptoms: coughing first, then nausea and vomiting, then severe health loss.\n\n";
		s += "Treat:\n- Rombiopental tablets (TerjePillsRombiopental), level 1\n- Neirocetal ampoule (TerjeAmpouleNeirocetal), level 2\n\nWear a gas mask with a filter in gas zones.";
		AddPage("Chemical poisoning", s);

		s = "Cause: close combat with infected; the chance rises sharply when they wound you. Masks and armor reduce the risk.\n\n";
		s += "The virus incubates for over an hour of real time. In the final stage health falls rapidly.\n\n";
		s += "Treat: Zivirol ampoule (TerjeAmpouleZivirol) or Zivirol injector (TerjeInjectorZivirol). Heavy overdose load - do not double up.\n";
		s += "Prevent: Zerivax vaccine (TerjeAmpouleZerivax).";
		AddPage("Zombie virus", s);

		s = "Cause: bites from infected animals such as wolves.\n\n";
		s += "Symptoms: none at first, then mild fever and weakness, worsening over time.\n\n";
		s += "Treat: Rabinoline ampoule (level 2), Rifampicin ampoule or Rabinucoline injector (level 3).\n";
		s += "Prevent: Rabivax vaccine (TerjeAmpouleRabivax).";
		AddPage("Rabies", s);

		s = "Only applies where radioactive zones exist. Use a dosimeter and protective suit.\n\n";
		s += "Anti-radiation drugs:\n";
		s += "Level 1: Potassium Iodide (TerjePillsPotassiumIodide), B-190 (TerjePillsB190), Hexacyanoferrate tablets.\n";
		s += "Level 2: Mexamine tablets, Pentacin and Carboxyme ampoules.\n";
		s += "Level 3: Anti-rad injector (TerjeAntiradInjector).\n\nDecontaminate gear after leaving a zone.";
		AddPage("Radiation", s);

		s = "Every medicine adds to your overdose level; it slowly wears off.\n\n";
		s += "Stage 1: nausea and hallucinations.\nStage 2: may lose consciousness.\nStage 3: critical health loss - can kill.\n\n";
		s += "Wait between doses and never take medicine you do not need.";
		AddPage("Overdose", s);

		s = "You need sleep like food and water. Yellow icon: yawning, vision worsens. Red: you may pass out.\n\n";
		s += "Sleep somewhere warm - fireplace, tent, house, sleeping bag. You cannot sleep while freezing, starving or seriously ill.\n\n";
		s += "Sleep restores health and blood and can cure mild illness. Energy drinks (MadBull, Gang, Yaguar, PrayBoy, 6Energy) keep you awake.";
		AddPage("Sleep", s);
	}
}

modded class MissionBase
{
	override UIScriptedMenu CreateScriptedMenu(int id)
	{
		if (id == EZ_MENU_MEDMANUAL)
		{
			EZMedManualMenu m = new EZMedManualMenu();
			m.SetID(id);
			return m;
		}
		return super.CreateScriptedMenu(id);
	}
}
