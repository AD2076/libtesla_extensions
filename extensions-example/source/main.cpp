#define TESLA_INIT_IMPL // If you have more than one file using the tesla header, only define this in the main one
#include <tesla.hpp>
#include <tesla_extensions.hpp>    // The Tesla Extensions Header


class GuiDoubleLayout1 : public tsl::Gui {
public:
    GuiDoubleLayout1() {}

    virtual tsl::elm::Element* createUI() override {
        auto *rootFrame = new tsl::elm::DoubleSectionOverlayFrame("Tesla Extensions Example", "Double Section Gui 1", tsl::SectionsLayout::big_bottom, true);
        auto *top_list = new tsl::elm::List();
        auto *bottom_list = new tsl::elm::List();

        for (int i = 0; i < 10; i++) {
            top_list->addItem(new tsl::elm::SmallListItem("Small List Item " + std::to_string(i)));
        }

        for (int i = 0; i < 10; i++) {
            bottom_list->addItem(new tsl::elm::SmallListItem("Small List Item " + std::to_string(i)));
        }

        rootFrame->setTopSection(top_list);
        rootFrame->setBottomSection(bottom_list);

        return rootFrame;
    }
};

class GuiDoubleLayout2 : public tsl::Gui {
public:
    GuiDoubleLayout2() {}

    virtual tsl::elm::Element* createUI() override {
        auto *rootFrame = new tsl::elm::DoubleSectionOverlayFrame("Tesla Extensions Example", "Double Section Gui 2", tsl::SectionsLayout::same, true);
        auto *top_list = new tsl::elm::List();
        auto *bottom_list = new tsl::elm::List();

        for (int i = 0; i < 10; i++) {
            top_list->addItem(new tsl::elm::SmallListItem("Small List Item " + std::to_string(i)));   
        }

        for (int i = 0; i < 10; i++) {
            bottom_list->addItem(new tsl::elm::SmallListItem("Small List Item " + std::to_string(i)));
        }

        rootFrame->setTopSection(top_list);
        rootFrame->setBottomSection(bottom_list);

        return rootFrame;
    }
};

class GuiDoubleLayout3 : public tsl::Gui {
public:
    GuiDoubleLayout3() {}

    virtual tsl::elm::Element* createUI() override {
        auto *rootFrame = new tsl::elm::DoubleSectionOverlayFrame("Tesla Extensions Example", "Double Section Gui 3", tsl::SectionsLayout::big_top, true);
        auto *top_list = new tsl::elm::List();
        auto *bottom_list = new tsl::elm::List();

        for (int i = 0; i < 10; i++) {
            top_list->addItem(new tsl::elm::SmallListItem("Small List Item " + std::to_string(i)));
        }

        for (int i = 0; i < 10; i++) {
            bottom_list->addItem(new tsl::elm::SmallListItem("Small List Item " + std::to_string(i)));
        }

        rootFrame->setTopSection(top_list);
        rootFrame->setBottomSection(bottom_list);

        return rootFrame;
    }
};

class GuiTest : public tsl::Gui {
public:
    GuiTest(u8 arg1, u8 arg2, bool arg3) { }

    // Called when this Gui gets loaded to create the UI
    // Allocate all elements on the heap. libtesla will make sure to clean them up when not needed anymore
    virtual tsl::elm::Element* createUI() override {
        // A OverlayFrame is the base element every overlay consists of. This will draw the default Title and Subtitle.
        // If you need more information in the header or want to change it's look, use a HeaderOverlayFrame.
        auto frame = new tsl::elm::OverlayFrame("Tesla Extensions Example", "v0.0.1");

        // A list that can contain sub elements and handles scrolling
        auto list = new tsl::elm::List();

        // List Items
        // A Bigger Category Header
        list->addItem(new tsl::elm::BigCategoryHeader("Big Category Header"));

        // Category header with text, separator, alwaysSmall
        // Standard Category header is small only when it's first item in list. With this you can choose
        list->addItem(new tsl::elm::CustomCategoryHeader("Custom Category Header", true, true));

        // Category header with text and without separator and alwaysSmall
        // Standard Category header is small only when it's first item in list. With this you can choose
        list->addItem(new tsl::elm::CustomCategoryHeader("Custom Category Header", false, false));       

        auto *doubleSection1 = new tsl::elm::SmallListItem("Double Section");
        //set standard value, highlight color
        doubleSection1->setValue("1:3 / 2:3");

        doubleSection1->setClickListener([](u64 keys) { 
            if (keys & KEY_A) {
                tsl::changeTo<GuiDoubleLayout1>();
                return true;
            }

            return false;
        });
        list->addItem(doubleSection1);
        
        auto *doubleSection2 = new tsl::elm::SmallListItem("Double Section");
        //set faint value, description color
        doubleSection2->setValue("1/2 : 1/2", true);

        doubleSection2->setClickListener([](u64 keys) { 
            if (keys & KEY_A) {
                tsl::changeTo<GuiDoubleLayout2>();
                return true;
            }

            return false;
        });
        list->addItem(doubleSection2);

        auto *doubleSection3 = new tsl::elm::SmallListItem("Double Section");
        //set colored value, choose your color
        doubleSection3->setColoredValue("2/3 : 1/3", tsl::style::color::ColorWarning);
        doubleSection3->setClickListener([](u64 keys) { 
            if (keys & KEY_A) {
                tsl::changeTo<GuiDoubleLayout3>();
                return true;
            }

            return false;
        });
        list->addItem(doubleSection3);

        // Add the list to the frame for it to be drawn
        frame->setContent(list);
        
        // Return the frame to have it become the top level element of this Gui
        return frame;
    }

    // Called once every frame to update values
    virtual void update() override {

    }

    // Called once every frame to handle inputs not handled by other UI elements
    virtual bool handleInput(u64 keysDown, u64 keysHeld, touchPosition touchInput, JoystickPosition leftJoyStick, JoystickPosition rightJoyStick) override {
        return false;   // Return true here to singal the inputs have been consumed
    }
};

class OverlayTest : public tsl::Overlay {
public:
                                             // libtesla already initialized fs, hid, pl, pmdmnt, hid:sys and set:sys
    virtual void initServices() override {}  // Called at the start to initialize all services necessary for this Overlay
    virtual void exitServices() override {}  // Callet at the end to clean up all services previously initialized

    virtual void onShow() override {}    // Called before overlay wants to change from invisible to visible state
    virtual void onHide() override {}    // Called before overlay wants to change from visible to invisible state

    virtual std::unique_ptr<tsl::Gui> loadInitialGui() override {
        return initially<GuiTest>(1, 2, true);  // Initial Gui to load. It's possible to pass arguments to it's constructor like this
    }
};

int main(int argc, char **argv) {
    return tsl::loop<OverlayTest>(argc, argv);
}
