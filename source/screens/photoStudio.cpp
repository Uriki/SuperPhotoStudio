#include "photoStudio.hpp"
#include "screenvars.h"

#include "file_browse.h"

#include "import_ss1charnames.h"
#include "import_ss2charnames.h"
#include "import_ss3charnames.h"
#include "import_ss4charnames.h"
#include "rocketcharnames.h"
#include "smCharNames.h"
#include "sthCharNames.h"
#include "jfgCharNames.h"
#include "conkerCharNames.h"
#include "banjokCharNames.h"
#include "pacCharNames.h"

#include "import_ss1bgnames.h"
#include "import_ss2bgnames.h"
#include "import_ss3bgnames.h"
#include "import_ss4bgnames.h"
#include "pdarkBgNames.h"
#include "smBgNames.h"

#include <unistd.h>

static int charPageOrder[] = {
	4,	// Super Photo Studio (Original Characters)
	9,	// Banjo-Kazooie series
	8,	// Conker series
	7,	// Jet Force Gemini
	10,	// Pac-Man series
	5,	// Super Mario series
	6,	// Sonic the Hedgehog series
	0,	// Style Savvy
	1,	// Style Savvy: Trendsetters
	2,	// Style Savvy: Fashion Forward
	3};	// Style Savvy: Styling Star

static int metalXpos = 0;
static int currentCharacterRendered = 0;
extern bool musicPlayStarted;
extern bool clearTop;
extern bool renderTop;

PhotoStudio::PhotoStudio() {
	currentCharacterRendered = 0;
	GFX::resetCharStatus();
	getList();
}

void PhotoStudio::getList() {
	getMaxChars();
}

void PhotoStudio::getMaxChars() {
	if (subScreenMode == 1) {
		// Locations
		if (photo_highlightedGame == 6) {
			import_totalCharacters = 1;
		} else if (photo_highlightedGame == 5) {
			import_totalCharacters = 0;
		} else if (photo_highlightedGame == 4) {
			import_totalCharacters = 0;
		} else if (photo_highlightedGame == 3) {
			import_totalCharacters = 11;
		} else if (photo_highlightedGame == 2) {
			import_totalCharacters = 8;
		} else if (photo_highlightedGame == 1) {
			import_totalCharacters = 27;
		} else if (photo_highlightedGame == 0) {
			import_totalCharacters = 2;
		}
	} else {
		// Characters
		const int highlightedGame = char_highlightedGame[currentCharNum];
		if (charPageOrder[highlightedGame] == 10) {
			import_totalCharacters = 1;
		} else if (charPageOrder[highlightedGame] == 9) {
			import_totalCharacters = 4;
		} else if (charPageOrder[highlightedGame] == 8) {
			import_totalCharacters = 1;
		} else if (charPageOrder[highlightedGame] == 7) {
			import_totalCharacters = 1;
		} else if (charPageOrder[highlightedGame] == 6) {
			import_totalCharacters = 0;
		} else if (charPageOrder[highlightedGame] == 5) {
			import_totalCharacters = 3;
		} else if (charPageOrder[highlightedGame] == 4) {
			import_totalCharacters = 3;
		} else if (charPageOrder[highlightedGame] == 3) {
			import_totalCharacters = 0xD;
		} else if (charPageOrder[highlightedGame] == 2) {
			import_totalCharacters = 0x10;
		} else if (charPageOrder[highlightedGame] == 1) {
			import_totalCharacters = 0x12;
		} else if (charPageOrder[highlightedGame] == 0) {
			import_totalCharacters = 0x7;
		}
	}
}

const char* PhotoStudio::seasonName(void) const {
	switch (seasonNo[currentCharNum]) {
		case 0:
			return "Spring";
		case 1:
			return "Summer";
		case 2:
			return "Fall";
		case 3:
			return "Winter";
	}
	
	return "null";
}

const char* PhotoStudio::import_characterName(void) const {
	switch (charPageOrder[char_highlightedGame[currentCharNum]]) {
		case 0:
			return import_ss1CharacterNames[importCharacterList_cursorPosition[currentCharNum]];
		case 1:
			return import_ss2CharacterNames[importCharacterList_cursorPosition[currentCharNum]];
		case 2:
			return import_ss3CharacterNames[importCharacterList_cursorPosition[currentCharNum]];
		case 3:
			return import_ss4CharacterNames[importCharacterList_cursorPosition[currentCharNum]];
		case 4:
			return rocketCharacterNames[importCharacterList_cursorPosition[currentCharNum]];
		case 5:
			return smCharacterNames[importCharacterList_cursorPosition[currentCharNum]];
		case 6:
			return sthCharacterNames[importCharacterList_cursorPosition[currentCharNum]];
		case 7:
			return jfgCharacterNames[importCharacterList_cursorPosition[currentCharNum]];
		case 8:
			return conkerCharacterNames[importCharacterList_cursorPosition[currentCharNum]];
		case 9:
			return banjokCharacterNames[importCharacterList_cursorPosition[currentCharNum]];
		case 10:
			return pacCharacterNames[importCharacterList_cursorPosition[currentCharNum]];
	}
	return "null";
}

const char* PhotoStudio::import_characterFileName(void) const {
	switch (charPageOrder[char_highlightedGame[currentCharNum]]) {
		case 3:
		switch (seasonNo[currentCharNum]) {
			case 0:
				return ss4CharacterFileNamesSpring[importCharacterList_cursorPosition[currentCharNum]];
			case 1:
				return ss4CharacterFileNamesSummer[importCharacterList_cursorPosition[currentCharNum]];
			case 2:
				return ss4CharacterFileNamesFall[importCharacterList_cursorPosition[currentCharNum]];
			case 3:
				return ss4CharacterFileNamesWinter[importCharacterList_cursorPosition[currentCharNum]];
		}
		case 4:
		switch (seasonNo[currentCharNum]) {
			case 0:
				return rocketCharacterFileNamesSpring[importCharacterList_cursorPosition[currentCharNum]];
			case 1:
				return rocketCharacterFileNamesSummer[importCharacterList_cursorPosition[currentCharNum]];
			case 2:
				return rocketCharacterFileNamesFall[importCharacterList_cursorPosition[currentCharNum]];
			case 3:
				return rocketCharacterFileNamesWinter[importCharacterList_cursorPosition[currentCharNum]];
		}
		case 5:
		switch (seasonNo[currentCharNum]) {
			case 0:
				return smCharacterFileNamesSpring[importCharacterList_cursorPosition[currentCharNum]];
			case 1:
				return smCharacterFileNamesSummer[importCharacterList_cursorPosition[currentCharNum]];
			case 2:
				return smCharacterFileNamesFall[importCharacterList_cursorPosition[currentCharNum]];
			case 3:
				return smCharacterFileNamesWinter[importCharacterList_cursorPosition[currentCharNum]];
		}
		case 6:
		switch (seasonNo[currentCharNum]) {
			case 0:
				return sthCharacterFileNamesSpring[importCharacterList_cursorPosition[currentCharNum]];
			case 1:
				return sthCharacterFileNamesSummer[importCharacterList_cursorPosition[currentCharNum]];
			case 2:
				return sthCharacterFileNamesFall[importCharacterList_cursorPosition[currentCharNum]];
			case 3:
				return sthCharacterFileNamesWinter[importCharacterList_cursorPosition[currentCharNum]];
		}
		case 7:
		switch (seasonNo[currentCharNum]) {
			case 0:
				return jfgCharacterFileNamesSpring[importCharacterList_cursorPosition[currentCharNum]];
			case 1:
				return jfgCharacterFileNamesSummer[importCharacterList_cursorPosition[currentCharNum]];
			case 2:
				return jfgCharacterFileNamesFall[importCharacterList_cursorPosition[currentCharNum]];
			case 3:
				return jfgCharacterFileNamesWinter[importCharacterList_cursorPosition[currentCharNum]];
		}
		case 8:
		switch (seasonNo[currentCharNum]) {
			case 0:
				return conkerCharacterFileNamesSpring[importCharacterList_cursorPosition[currentCharNum]];
			case 1:
				return conkerCharacterFileNamesSummer[importCharacterList_cursorPosition[currentCharNum]];
			case 2:
				return conkerCharacterFileNamesFall[importCharacterList_cursorPosition[currentCharNum]];
			case 3:
				return conkerCharacterFileNamesWinter[importCharacterList_cursorPosition[currentCharNum]];
		}
		case 9:
		switch (seasonNo[currentCharNum]) {
			case 0:
				return banjokCharacterFileNamesSpring[importCharacterList_cursorPosition[currentCharNum]];
			case 1:
				return banjokCharacterFileNamesSummer[importCharacterList_cursorPosition[currentCharNum]];
			case 2:
				return banjokCharacterFileNamesFall[importCharacterList_cursorPosition[currentCharNum]];
			case 3:
				return banjokCharacterFileNamesWinter[importCharacterList_cursorPosition[currentCharNum]];
		}
		case 10:
		switch (seasonNo[currentCharNum]) {
			case 0:
				return pacCharacterFileNamesSpring[importCharacterList_cursorPosition[currentCharNum]];
			case 1:
				return pacCharacterFileNamesSummer[importCharacterList_cursorPosition[currentCharNum]];
			case 2:
				return pacCharacterFileNamesFall[importCharacterList_cursorPosition[currentCharNum]];
			case 3:
				return pacCharacterFileNamesWinter[importCharacterList_cursorPosition[currentCharNum]];
		}
	}
	return "null";
}

const char* PhotoStudio::import_SS2CharacterNames(int i) const {
	switch (sysRegion) {
		default:
			return import_ss2CharacterNames[i];
		case CFG_REGION_EUR:
		case CFG_REGION_AUS:
			return import_nsbCharacterNames[i];
	}
}

const char* PhotoStudio::ss1Title(void) const {
	switch (sysRegion) {
		default:
			return "Style Savvy";
		case CFG_REGION_EUR:
		case CFG_REGION_AUS:
			return "Style Boutique";
		case CFG_REGION_JPN:
			return "Wagamama Fashion: Girls Mode";
		case CFG_REGION_KOR:
			return "Namanui Collection: Girls Style";
	}
}

const char* PhotoStudio::ss2Title(void) const {
	switch (sysRegion) {
		default:
			return "Style Savvy: Trendsetters";
		case CFG_REGION_EUR:
		case CFG_REGION_AUS:
			return "New Style Boutique";
		case CFG_REGION_JPN:
			return "Girls Mode: Yokubari Sengen";
		case CFG_REGION_KOR:
			return "Girls Style: Paesyeon Lideo Seon-eon!";
	}
}

const char* PhotoStudio::ss3Title(void) const {
	switch (sysRegion) {
		default:
			return "Style Savvy: Fashion Forward";
		case CFG_REGION_EUR:
		case CFG_REGION_AUS:
			return "New Style Boutique 2: Fashion Forward";
		case CFG_REGION_JPN:
			return "Girls Mode 3: Kirakira * Code";
		case CFG_REGION_KOR:
			return "Girls Style: Kirakira * Code";
	}
}

const char* PhotoStudio::ss4Title(void) const {
	switch (sysRegion) {
		default:
			return "Style Savvy: Styling Star";
		case CFG_REGION_EUR:
		case CFG_REGION_AUS:
			return "New Style Boutique 3: Styling Star";
		case CFG_REGION_JPN:
			return "Girls Mode 4: Star Stylist";
		case CFG_REGION_KOR:
			return "Girls Style: Star Stylist";
	}
}

int PhotoStudio::getBgNum(void) const {
	switch (photo_highlightedGame) {
		case 0:
			return import_ss1BgNums[bgList_cursorPosition];
		case 1:
			return import_ss2BgNums[bgList_cursorPosition];
		case 2:
			return import_ss3BgNums[bgList_cursorPosition];
		case 3:
			return import_ss4BgNums[bgList_cursorPosition];
		case 5:
			return pdarkBgNums[bgList_cursorPosition];
		case 6:
			return smBgNums[bgList_cursorPosition];
	}
	return 0;
}

void PhotoStudio::drawMsg(void) const {
	GFX::DrawSprite(sprites_msg_idx, 0, 8, 1, 1);
	GFX::DrawSprite(sprites_msg_idx, 160, 8, -1, 1);
	GFX::DrawSprite(messageNo == 4 ? sprites_icon_question_idx : sprites_icon_msg_idx, 132, -2);

	Gui::DrawStringCentered(0, 84, 0.60, BLACK, "Please remove latest");
	Gui::DrawStringCentered(0, 104, 0.60, BLACK, "character(s) first.");

	GFX::DrawSprite(sprites_button_msg_shadow_idx, 114, 197);
	GFX::DrawSprite(sprites_button_msg_idx, 115, 188);
	Gui::DrawString(134, 196, 0.70, MSG_BUTTONTEXT, " OK!");
}

void PhotoStudio::loadChrImage(void) {
	previewCharacter = false;
	gspWaitForVBlank();
	if (charPageOrder[char_highlightedGame[currentCharNum]] >= 3) {
		/*if (numberOfExportedCharacters > 0) {
			sprintf(chrFilePath, "sdmc:/3ds/SavvyManager/SS%i/characters/previews/%s.t3x", 4, getExportedCharacterName(importCharacterList_cursorPosition[currentCharNum]));	// All Seasons
		} else {
			sprintf(chrFilePath, "romfs:/gfx/null.t3x");	// All Seasons
		}*/
		sprintf(chrFilePath, "romfs:/gfx/%s.t3x", import_characterFileName());
		previewCharacterFound[currentCharNum] = GFX::loadCharSprite(currentCharNum, chrFilePath, chrFilePath);
	} else {
		sprintf(chrFilePath, "romfs:/gfx/ss%i_%s.t3x", 4, import_characterName());				// All Seasons
		sprintf(chrFilePath2, "romfs:/gfx/ss%i_%s%i.t3x", 4, import_characterName(), seasonNo[currentCharNum]);	// One Season
		previewCharacterFound[currentCharNum] = GFX::loadCharSprite(currentCharNum, chrFilePath, chrFilePath2);
	}
	if (previewCharacterFound[0] && !characterPicked[1]) {
		GFX::loadCharSpriteMem(0);
	}
	previewCharacter = true;
}


void PhotoStudio::Draw(void) const {
	animateBg = bgCanAnimate;

	if (!musicPlayStarted) {
		extern void Play_Music();
		Play_Music();
		musicPlayStarted = true;
	}

  if (renderTop) {
	Gui::ScreenDraw(Top);

	preview();

	if (currentCharacterRendered == 0) {
		if (displayStudioBg) {
			GFX::showBgSprite(zoomIn);
		} else if (showScrollingBg) {
			GFX::DrawSpriteLinear(sprites_titleMetal_idx, metalXpos, 0, 16, 16);
			metalXpos--;
			if (metalXpos < -8*16) {
				metalXpos = 0;
			}
			GFX::DrawSprite(sprites_title_idx, 0, 0, 0.5);
		} else {
			Gui::Draw_Rect(0, 0, 400, 240, WHITE);
		}
		if (previewCharacter) {
			if (previewCharacterFound[0]) {
				if (characterPicked[1]) {
					GFX::loadCharSpriteMem(0);
				}
				GFX::showCharSprite(0, characterFlipH[0], zoomIn, charFadeAlpha, displayStudioBg);
			} else {
				Gui::DrawStringCentered(0, 104, 0.65, WHITE, (/*charPageOrder[char_highlightedGame[currentCharNum]]==4 ? "Preview not found." :*/ "Preview unavailable."));
			}
		}
	} else {
		if (characterPicked[currentCharacterRendered] && previewCharacterFound[currentCharacterRendered]) {
			GFX::loadCharSpriteMem(currentCharacterRendered);
			GFX::showCharSprite(currentCharacterRendered, characterFlipH[currentCharacterRendered], zoomIn, charFadeAlpha, displayStudioBg);
		}
	}

	if (renderTop && subScreenMode!=1 && previewCharacter && previewCharacterFound[0] && previewCharacterFound[1]) {
		currentCharacterRendered++;
		if (currentCharacterRendered > charsShown) {
			currentCharacterRendered = 0;
			renderTop = false;
		}
		clearTop = (currentCharacterRendered == 0);
	}

	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
  }

	if (cinemaWide) {
		Gui::Draw_Rect(0, 0, 400, 36, C2D_Color32(0, 0, 0, 255));
		Gui::Draw_Rect(0, 204, 400, 36, C2D_Color32(0, 0, 0, 255));
	}

	if (shiftBySubPixel) {
		Gui::Draw_Rect(0, 239, 400, 1, C2D_Color32(0, 0, 0, 255));
		return;
	}
	Gui::ScreenDraw(Bottom);
	GFX::DrawSprite(sprites_photo_bg_idx, 0, 0);

	cursorX = 248;
	if (subScreenMode == 10) {
		SettingsDraw();
	} else if (subScreenMode == 2) {
		cursorY = 64+(48*importCharacterList_cursorPositionOnScreen[currentCharNum]);

		// Game name
		switch (charPageOrder[char_highlightedGame[currentCharNum]]) {
			case 10:
				Gui::DrawStringCentered(0, 8, 0.50, WHITE, "Pac-Man series");
				break;
			case 9:
				Gui::DrawStringCentered(0, 8, 0.50, WHITE, "Banjo-Kazooie series");
				break;
			case 8:
				Gui::DrawStringCentered(0, 8, 0.50, WHITE, "Conker series");
				break;
			case 7:
				Gui::DrawStringCentered(0, 8, 0.50, WHITE, "Jet Force Gemini");
				break;
			case 6:
				Gui::DrawStringCentered(0, 8, 0.50, WHITE, "Sonic the Hedgehog series");
				break;
			case 5:
				Gui::DrawStringCentered(0, 8, 0.50, WHITE, "Super Mario series");
				break;
			case 4:
				Gui::DrawStringCentered(0, 8, 0.50, WHITE, "Super Photo Studio");
				break;
			case 3:
				Gui::DrawStringCentered(0, 8, 0.50, WHITE, ss4Title());
				break;
			case 2:
				Gui::DrawStringCentered(0, 8, 0.50, WHITE, ss3Title());
				break;
			case 1:
				Gui::DrawStringCentered(0, 8, 0.50, WHITE, ss2Title());
				break;
			case 0:
				Gui::DrawStringCentered(0, 8, 0.50, WHITE, ss1Title());
				break;
		}
		Gui::DrawString(8, 8, 0.50, WHITE, "<");
		Gui::DrawString(304, 8, 0.50, WHITE, ">");

		if (currentCharNum > 0) {
			Gui::DrawString(96, 184, 0.55, WHITE, ": Remove character");
		}

		//if (charPageOrder[char_highlightedGame[currentCharNum]] != 4) {
			// Selected season
			Gui::DrawString(120-36, 208, 0.65, WHITE, "L");
			Gui::DrawStringCentered(-36, 210, 0.50, WHITE, seasonName());
			Gui::DrawString(192-36, 208, 0.65, WHITE, "R");
		//}

		Gui::DrawString(184, 208, 0.65, WHITE, "SELECT: Flip H");

	  if (!displayNothing) {
		int i2 = 48;
		for (int i = import_characterShownFirst[currentCharNum]; i < import_characterShownFirst[currentCharNum]+3; i++) {
			if (charPageOrder[char_highlightedGame[currentCharNum]] == 10) {
				if (i >= 2) break;
				GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
				GFX::DrawSprite((pacCharacterGenders[i] ? sprites_icon_male_idx : sprites_icon_female_idx), 12, i2-8);
				Gui::DrawString(64, i2, 0.65, WHITE, pacCharacterNames[i]);
			} else if (charPageOrder[char_highlightedGame[currentCharNum]] == 9) {
				GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
				GFX::DrawSprite((banjokCharacterGenders[i] ? sprites_icon_male_idx : sprites_icon_female_idx), 12, i2-8);
				Gui::DrawString(64, i2, 0.65, WHITE, banjokCharacterNames[i]);
			} else if (charPageOrder[char_highlightedGame[currentCharNum]] == 8) {
				if (i >= 2) break;
				GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
				GFX::DrawSprite((conkerCharacterGenders[i] ? sprites_icon_male_idx : sprites_icon_female_idx), 12, i2-8);
				Gui::DrawString(64, i2, 0.65, WHITE, conkerCharacterNames[i]);
			} else if (charPageOrder[char_highlightedGame[currentCharNum]] == 7) {
				if (i >= 2) break;
				GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
				GFX::DrawSprite((jfgCharacterGenders[i] ? sprites_icon_male_idx : sprites_icon_female_idx), 12, i2-8);
				Gui::DrawString(64, i2, 0.65, WHITE, jfgCharacterNames[i]);
			} else if (charPageOrder[char_highlightedGame[currentCharNum]] == 6) {
				if (i >= 1) break;
				GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
				GFX::DrawSprite((sthCharacterGenders[i] ? sprites_icon_male_idx : sprites_icon_female_idx), 12, i2-8);
				Gui::DrawString(64, i2, 0.65, WHITE, sthCharacterNames[i]);
			} else if (charPageOrder[char_highlightedGame[currentCharNum]] == 5) {
				GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
				GFX::DrawSprite((smCharacterGenders[i] ? sprites_icon_male_idx : sprites_icon_female_idx), 12, i2-8);
				Gui::DrawString(64, i2, 0.65, WHITE, smCharacterNames[i]);
			} else if (charPageOrder[char_highlightedGame[currentCharNum]] == 4) {
				GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
				GFX::DrawSprite((rocketCharacterGenders[i] ? sprites_icon_male_idx : sprites_icon_female_idx), 12, i2-8);
				Gui::DrawString(64, i2, 0.65, WHITE, rocketCharacterNames[i]);
			} else if (charPageOrder[char_highlightedGame[currentCharNum]] == 3) {
				GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
				GFX::DrawSprite((import_ss4CharacterGenders[i] ? sprites_icon_male_idx : sprites_icon_female_idx), 12, i2-8);
				Gui::DrawString(64, i2, 0.65, WHITE, import_ss4CharacterNames[i]);
			} else if (charPageOrder[char_highlightedGame[currentCharNum]] == 2) {
				GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
				GFX::DrawSprite((import_ss3CharacterGenders[i] ? sprites_icon_male_idx : sprites_icon_female_idx), 12, i2-8);
				Gui::DrawString(64, i2, 0.65, WHITE, import_ss3CharacterNames[i]);
			} else if (charPageOrder[char_highlightedGame[currentCharNum]] == 1) {
				GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
				GFX::DrawSprite((import_ss2CharacterGenders[i] ? sprites_icon_male_idx : sprites_icon_female_idx)/*+import_ss2CharacterTieColors[i]*/, 12, i2-8);
				Gui::DrawString(64, i2, 0.65, WHITE, import_SS2CharacterNames(i));
			} else if (charPageOrder[char_highlightedGame[currentCharNum]] == 0) {
				GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
				GFX::DrawSprite((import_ss1CharacterGenders[i] ? sprites_icon_male_idx : sprites_icon_female_idx), 12, i2-8);
				Gui::DrawString(64, i2, 0.65, WHITE, import_ss1CharacterNames[i]);
			}
			i2 += 48;
		}
	  }
	} else if (subScreenMode == 1) {
		cursorY = 64+(48*bgList_cursorPositionOnScreen);

		// Game name
		switch (photo_highlightedGame) {
			case 6:
				Gui::DrawStringCentered(0, 8, 0.50, WHITE, "Super Mario series");
				break;
			case 5:
				Gui::DrawStringCentered(0, 8, 0.50, WHITE, "Perfect Dark");
				break;
			case 4:
				Gui::DrawStringCentered(0, 8, 0.50, WHITE, "Super Photo Studio");
				break;
			case 3:
				Gui::DrawStringCentered(0, 8, 0.50, WHITE, ss4Title());
				break;
			case 2:
				Gui::DrawStringCentered(0, 8, 0.50, WHITE, ss3Title());
				break;
			case 1:
				Gui::DrawStringCentered(0, 8, 0.50, WHITE, ss2Title());
				break;
			case 0:
				Gui::DrawStringCentered(0, 8, 0.50, WHITE, ss1Title());
				break;
		}
		Gui::DrawString(8, 8, 0.50, WHITE, "<");
		Gui::DrawString(304, 8, 0.50, WHITE, ">");

		/*if (photo_highlightedGame != 4) {
			// Selected season
			Gui::DrawString(120, 208, 0.65, BLACK, "L");
			Gui::DrawStringCentered(0, 210, 0.50, BLACK, seasonName());
			Gui::DrawString(192, 208, 0.65, BLACK, "R");
		}*/

	  if (!displayNothing) {
		int i2 = 48;
		for (int i = import_bgShownFirst; i < import_bgShownFirst+3; i++) {
			if (photo_highlightedGame == 6) {
				if (i >= 2) break;
				GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
				Gui::DrawString(32, i2, 0.65, WHITE, smBgNames[i]);
			} else if (photo_highlightedGame == 5) {
				if (i >= 1) break;
				GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
				Gui::DrawString(32, i2, 0.65, WHITE, pdarkBgNames[i]);
			} else if (photo_highlightedGame == 3) {
				GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
				Gui::DrawString(32, i2, 0.65, WHITE, import_ss4BgNames[i]);
			} else if (photo_highlightedGame == 2) {
				GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
				Gui::DrawString(32, i2, 0.65, WHITE, import_ss3BgNames[i]);
			} else if (photo_highlightedGame == 1) {
				GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
				Gui::DrawString(32, i2, 0.65, WHITE, import_ss2BgNames[i]);
			} else if (photo_highlightedGame == 0) {
				GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
				Gui::DrawString(32, i2, 0.65, WHITE, import_ss1BgNames[i]);
			}
			i2 += 48;
		}
	  }
	} else {
		cursorY = 64+(48*characterChangeMenu_cursorPositionOnScreen);

		Gui::DrawString(8, 8, 0.50, WHITE, "What do you want to do?");

		Gui::DrawString(192, 206, 0.65, WHITE, ": Take photo");

		int i2 = 0;
		i2 += 48;
		GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
		Gui::DrawString(32, i2, 0.65, WHITE, "Change location");
		i2 += 48;
		GFX::DrawSprite(sprites_item_button_idx, 16, i2-20);
		if (currentCharNum==4) {
			Gui::DrawString(32, i2, 0.65, WHITE, characterPicked[4] ? "Change character < 5 >" : "Add character < 5 >");
		} else if (currentCharNum==3) {
			Gui::DrawString(32, i2, 0.65, WHITE, characterPicked[3] ? "Change character < 4 >" : "Add character < 4 >");
		} else if (currentCharNum==2) {
			Gui::DrawString(32, i2, 0.65, WHITE, characterPicked[2] ? "Change character < 3 >" : "Add character < 3 >");
		} else if (currentCharNum==1) {
			Gui::DrawString(32, i2, 0.65, WHITE, characterPicked[1] ? "Change character < 2 >" : "Add character < 2 >");
		} else {
			Gui::DrawString(32, i2, 0.65, WHITE, "Change character < 1 >");
		}
	}

	if (subScreenMode != 0) {
		GFX::DrawSprite(sprites_button_shadow_idx, 5, 199);
		GFX::DrawSprite(sprites_button_red_idx, 5, 195);
		GFX::DrawSprite(sprites_arrow_back_idx, 19, 195);
		GFX::DrawSprite(sprites_button_b_idx, 44, 218);
	}

	GFX::drawCursor(cursorX, cursorY);

	if (showMessage) {
		drawMsg();
	}

	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
}

void PhotoStudio::preview() const {
	if (characterPicked[1]) {
		charFadeAlpha = 255;
	} else if (previewCharacter) {
		switch (iFps) {
			default:
				charFadeAlpha += 20;
				break;
			case 30:
				charFadeAlpha += 40;
				break;
			case 24:
				charFadeAlpha += 55;
				break;
		}
		if (charFadeAlpha > 255) charFadeAlpha = 255;
	} else {
		charFadeAlpha = 0;
	}
}



void PhotoStudio::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if ((subScreenMode==0 || subScreenMode==2) && (!characterPicked[1] || (characterPicked[1] && !renderTop)) && !characterPicked[3]) {
		int zoomLimit = characterPicked[1] ? 1 : 2;
		if (hDown & KEY_CPAD_UP) {
			zoomIn++;
			if (zoomIn > zoomLimit) {
				zoomIn = zoomLimit;
			} else {
				renderTop = true;
			}
		}
		if (hDown & KEY_CPAD_DOWN) {
			zoomIn--;
			if (zoomIn < 0) {
				zoomIn = 0;
			} else {
				renderTop = true;
			}
		}
	}

	if (showMessage) {
		if ((hDown & KEY_A) || ((hDown & KEY_TOUCH) && touch.px >= 115 && touch.px < 115+90 && touch.py >= 188 && touch.py < 188+47)) {
			sndSelect();
			showMessage = false;
		}
	} else if (subScreenMode == 10) {
		SettingsLogic(hDown, hHeld, touch);
	} else if (subScreenMode == 2) {
		if (showCursor) {
			if (hDown & KEY_DUP) {
				sndHighlight();
				importCharacterList_cursorPosition[currentCharNum]--;
				importCharacterList_cursorPositionOnScreen[currentCharNum]--;
				if (importCharacterList_cursorPosition[currentCharNum] < 0) {
					importCharacterList_cursorPosition[currentCharNum] = 0;
					import_characterShownFirst[currentCharNum] = 0;
				} else if (importCharacterList_cursorPosition[currentCharNum] < import_characterShownFirst[currentCharNum]) {
					import_characterShownFirst[currentCharNum]--;
				}
				if (importCharacterList_cursorPositionOnScreen[currentCharNum] < 0) {
					importCharacterList_cursorPositionOnScreen[currentCharNum] = 0;
				}
				renderTop = true;
				loadChrImage();
			}

			if (hDown & KEY_DDOWN) {
				sndHighlight();
				importCharacterList_cursorPosition[currentCharNum]++;
				importCharacterList_cursorPositionOnScreen[currentCharNum]++;
				if (importCharacterList_cursorPosition[currentCharNum] > import_totalCharacters) {
					importCharacterList_cursorPosition[currentCharNum] = import_totalCharacters;
					import_characterShownFirst[currentCharNum] = import_totalCharacters-2;
					if (import_characterShownFirst[currentCharNum] < 0) import_characterShownFirst[currentCharNum] = 0;
					if (importCharacterList_cursorPositionOnScreen[currentCharNum] > import_totalCharacters) {
						importCharacterList_cursorPositionOnScreen[currentCharNum] = import_totalCharacters;
					}
				} else if (importCharacterList_cursorPosition[currentCharNum] > import_characterShownFirst[currentCharNum]+2) {
					import_characterShownFirst[currentCharNum]++;
				}
				if (importCharacterList_cursorPositionOnScreen[currentCharNum] > 2) {
					importCharacterList_cursorPositionOnScreen[currentCharNum] = 2;
				}
				renderTop = true;
				loadChrImage();
			}
		}

		if (hDown & KEY_A) {
			sndSelect();
			subScreenMode = 0;
		}

		if ((hDown & KEY_X) && (currentCharNum > 0) && characterPicked[currentCharNum]) {
			if ((currentCharNum == 4) || !characterPicked[currentCharNum+1]) {
				sndSelect();
				characterPicked[currentCharNum] = false;
				previewCharacterFound[currentCharNum] = false;
				GFX::resetCharStatus(currentCharNum);
				currentCharNum--;
				charsShown--;
				subScreenMode = 0;
				renderTop = true;
				loadChrImage();
			} else {
				sndBack();
				showMessage = true;
			}
		}

		if (hDown & KEY_SELECT) {
			sndSelect();
			characterFlipH[currentCharNum] = !characterFlipH[currentCharNum];
			renderTop = true;
		}

		if (hDown & KEY_DLEFT) {
			sndHighlight();
			char_highlightedGame[currentCharNum]--;
			if (char_highlightedGame[currentCharNum] < 0) char_highlightedGame[currentCharNum] = 10;
			getMaxChars();
			renderTop = true;
		}

		if (hDown & KEY_DRIGHT) {
			sndHighlight();
			char_highlightedGame[currentCharNum]++;
			if (char_highlightedGame[currentCharNum] > 10) char_highlightedGame[currentCharNum] = 0;
			getMaxChars();
			renderTop = true;
		}

		if ((hDown & KEY_DLEFT) || (hDown & KEY_DRIGHT)) {
			importCharacterList_cursorPosition[currentCharNum] = 0;
			importCharacterList_cursorPositionOnScreen[currentCharNum] = 0;
			import_characterShownFirst[currentCharNum] = 0;
			/*if (charPageOrder[char_highlightedGame[currentCharNum]] == 4) {
				previewCharacter = false;
				if (!exportedCharListGotten) {
					displayNothing = true;
					gspWaitForVBlank();
					getExportedCharacterContents();
					exportedCharListGotten = true;
					displayNothing = false;
				}
			}*/
			getMaxChars();
			renderTop = true;
			loadChrImage();
		}

		//if (charPageOrder[char_highlightedGame[currentCharNum]] != 4) {
			if ((hDown & KEY_L) || (hDown & KEY_ZL)) {
				sndHighlight();
				seasonNo[currentCharNum]--;
				if (seasonNo[currentCharNum] < 0) seasonNo[currentCharNum] = 3;
				loadChrImage();
				renderTop = true;
			}

			if ((hDown & KEY_R) || (hDown & KEY_ZR)) {
				sndHighlight();
				seasonNo[currentCharNum]++;
				if (seasonNo[currentCharNum] > 3) seasonNo[currentCharNum] = 0;
				loadChrImage();
				renderTop = true;
			}
		//}

		if ((hDown & KEY_B) || ((hDown & KEY_TOUCH) && touchingBackButton())) {
			sndBack();
			subScreenMode = 0;
		}

	} else if (subScreenMode == 1) {
		if (showCursor) {
			if (hDown & KEY_DUP) {
				sndHighlight();
				bgList_cursorPosition--;
				bgList_cursorPositionOnScreen--;
				if (bgList_cursorPosition < 0) {
					bgList_cursorPosition = 0;
					import_bgShownFirst = 0;
				} else if (bgList_cursorPosition < import_bgShownFirst) {
					import_bgShownFirst--;
				}
				if (bgList_cursorPositionOnScreen < 0) {
					bgList_cursorPositionOnScreen = 0;
				}
				studioBg = getBgNum();
				displayStudioBg = false;
				gspWaitForVBlank();
				GFX::reloadBgSprite();
				displayStudioBg = true;
			}

			if (hDown & KEY_DDOWN) {
				sndHighlight();
				bgList_cursorPosition++;
				bgList_cursorPositionOnScreen++;
				if (bgList_cursorPosition > import_totalCharacters) {
					bgList_cursorPosition = import_totalCharacters;
					import_bgShownFirst = import_totalCharacters-2;
					if (import_bgShownFirst < 0) import_bgShownFirst = 0;
					if (bgList_cursorPositionOnScreen > import_totalCharacters) {
						bgList_cursorPositionOnScreen = import_totalCharacters;
					}
				} else if (bgList_cursorPosition > import_bgShownFirst+2) {
					import_bgShownFirst++;
				}
				if (bgList_cursorPositionOnScreen > 2) {
					bgList_cursorPositionOnScreen = 2;
				}
				studioBg = getBgNum();
				displayStudioBg = false;
				gspWaitForVBlank();
				GFX::reloadBgSprite();
				displayStudioBg = true;
			}
		}

		if (hDown & KEY_A) {
			sndSelect();
			subScreenMode = 0;
			previewCharacter = characterPicked[currentCharNum];
			if (characterPicked[3] && zoomIn < 1) {
				zoomIn = 1;
			}
		}

		if (hDown & KEY_DLEFT) {
			sndHighlight();
			photo_highlightedGame--;
			if (photo_highlightedGame == 4) photo_highlightedGame--;	// Skip Rocket Photo Shoot page for now
			if (photo_highlightedGame < 0) photo_highlightedGame = 6;
			getMaxChars();
		}

		if (hDown & KEY_DRIGHT) {
			sndHighlight();
			photo_highlightedGame++;
			if (photo_highlightedGame == 4) photo_highlightedGame++;	// Skip Rocket Photo Shoot page for now
			if (photo_highlightedGame > 6) photo_highlightedGame = 0;
			getMaxChars();
		}

		if ((hDown & KEY_DLEFT) || (hDown & KEY_DRIGHT)) {
			bgList_cursorPosition = 0;
			bgList_cursorPositionOnScreen = 0;
			import_bgShownFirst = 0;
			getMaxChars();
			studioBg = getBgNum();
			displayStudioBg = false;
			gspWaitForVBlank();
			GFX::reloadBgSprite();
			displayStudioBg = true;
		}

		if ((hDown & KEY_B) || ((hDown & KEY_TOUCH) && touchingBackButton())) {
			sndBack();
			subScreenMode = 0;
			previewCharacter = characterPicked[currentCharNum];
			if (characterPicked[3] && zoomIn < 1) {
				zoomIn = 1;
			}
		}

	} else {
		if (showCursor) {
			if (hDown & KEY_DUP) {
				sndHighlight();
				characterChangeMenu_cursorPosition--;
				characterChangeMenu_cursorPositionOnScreen--;
				if (characterChangeMenu_cursorPosition < 0) {
					characterChangeMenu_cursorPosition = 0;
				}
				if (characterChangeMenu_cursorPositionOnScreen < 0) {
					characterChangeMenu_cursorPositionOnScreen = 0;
				}
			}

			if (hDown & KEY_DDOWN) {
				sndHighlight();
				characterChangeMenu_cursorPosition++;
				characterChangeMenu_cursorPositionOnScreen++;
				if (characterChangeMenu_cursorPosition > 1) {
					characterChangeMenu_cursorPosition = 1;
				}
				if (characterChangeMenu_cursorPositionOnScreen > 1) {
					characterChangeMenu_cursorPositionOnScreen = 1;
				}
			}

			if (characterChangeMenu_cursorPosition == 1) {
				if (hDown & KEY_DLEFT) {
					sndHighlight();
					currentCharNum--;
					if (currentCharNum < 0) {
						currentCharNum = 0;
					}
				}
				if (hDown & KEY_DRIGHT) {
					sndHighlight();
					currentCharNum++;
					if (currentCharNum > charsShown+1) {
						currentCharNum = charsShown+1;
					}
					if (currentCharNum > 4) {
						currentCharNum = 4;
					}
				}
			}
		}

		if (hDown & KEY_A) {
			if (characterChangeMenu_cursorPosition == 0) {
				sndSelect();
				subScreenMode = 1;
				getMaxChars();
				previewCharacter = false;
				int bgNum = getBgNum();
				//if (studioBg != bgNum) {
					showScrollingBg = false;
					displayStudioBg = false;
					gspWaitForVBlank();
					studioBg = bgNum;
					GFX::reloadBgSprite();
					displayStudioBg = true;
				//}
				zoomIn = 0;
				renderTop = true;
			} else if (characterChangeMenu_cursorPosition == 1) {
				sndSelect();
				displayNothing = true;
				subScreenMode = 2;
				/*if ((subScreenMode == 2) && (charPageOrder[char_highlightedGame[currentCharNum]] == 4) && !exportedCharListGotten) {
					gspWaitForVBlank();
					getExportedCharacterContents();
					exportedCharListGotten = true;
				}*/
				getMaxChars();
				displayNothing = false;
				bool doCharLoad = !characterPicked[currentCharNum];
				if (!characterPicked[currentCharNum] && currentCharNum != 0) {
					charsShown++;
				}
				characterPicked[currentCharNum] = true;
				if (characterPicked[0] && characterPicked[1] && zoomIn > 1) {
					zoomIn = 1;
				}
				if (characterPicked[3] && zoomIn < 1) {
					zoomIn = 1;
				}
				if (doCharLoad) {
					renderTop = true;
					loadChrImage();
				}
			}
		}
	
		if (hDown & KEY_SELECT) {
			sndSelect();
			subScreenMode = 10;
		}
	}
}