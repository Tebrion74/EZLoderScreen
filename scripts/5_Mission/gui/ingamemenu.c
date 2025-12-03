modded class InGameMenu
{
    override Widget Init()
    {
        // Call vanilla / Expansion’s original Init
        layoutRoot = super.Init();

        // Try to find the existing logo widget and swap its image
        ReplaceExpansionLogo(layoutRoot);

        return layoutRoot;
    }

    void ReplaceExpansionLogo(Widget root)
    {
        if (!root)
            return;

        // Depth-first search through the widget tree
        Widget w = root.GetChildren();
        while (w)
        {
            ImageWidget img = ImageWidget.Cast(w);
            if (img)
            {
                // If we can inspect the current image name, we could filter here.
                // Some builds support these calls; if not, we just blunt-replace
                // the first image we find.
                // string setName;
                // string imageName;
                // img.GetImageSet(0, setName, imageName);

                // Swap to your EZ logo texture from your PBO
                img.LoadImageFile(0, "EZLoderScreen/data/ez_logo_mainmenu.paa");
                return; // stop after first image widget, which is usually the logo
            }

            // Recurse into children
            ReplaceExpansionLogo(w);

            w = w.GetSibling();
        }
    }
}
