#define DEFAULT_RECT(_vals) \
    _vals HORIZONTAL_ALIGN_DEFAULT VERTICAL_ALIGN_DEFAULT

#define NO_COLOR            .0 .0 .0 .0
#define LIGHT_COLOR         .9 .9 .9 1
#define LIGHTGREY_COLOR     .75 .75 .75 0.9
#define GREYISH_COLOR       .5 .5 .5 1
#define DARK_COLOR          .0 .0 .0 1
#define BLACK_COLOR         .0 .0 .0 1
#define WHITE_COLOR         1 1 1 1
#define MID_BLUE_COLOR      .0 .8 1.0 .8
#define BLUE_COLOR          .0 .1 0.5 1
#define BRIGHT_BLUE_COLOR   0.00 0.80 0.85 0.7
#define WHITE_TRANSPARENT_COLOR  1.0 1.0 1.0 0.1

#define BLACK_TRANSPARENT_COLOR  0 0 0 .5

#define BG_COLOR            0.13 0.14 0.16 0.70
#define BT_COLOR            0.13 0.14 0.16 0.20
#define BG_NAV_COLOR        0.13 0.14 0.16 1
#define BG_NAVSEP_COLOR     1 1 1 0.1
#define HIGHLIGHT_COLOR     0.00 0.80 0.85 1

#define OUTER_FRAME_SIZE_X        600//400
#define OUTER_FRAME_SIZE_Y        360//268
#define OUTER_FRAME_ORG_X         ((FULLSCREEN_X - OUTER_FRAME_SIZE_X) / 2)
#define OUTER_FRAME_ORG_Y         ((FULLSCREEN_Y - OUTER_FRAME_SIZE_Y) / 2)

#define H_SEP_ORG_Y             50

// Main OpenCJ theme colors
#define RAISIN_COLOR        0.08235 0.08627 0.1451 1
#define YINMN_BLUE_COLOR    0.2862 0.3059 0.4118 1
#define GLAUCOUS_COLOR      0.4078 0.4392 0.5843 1
#define ALICE_BLUE_COLOR    0.8745 0.9294 1 1
#define PERIWINKLE_COLOR    0.7490 0.7961 1 1

// Other colors
#define MILD_GREEN_COLOR    0.2 0.7490 0.2 1
#define RED_COLOR           1.0 0.1 0.1 0.95
#define GREEN_COLOR         0.1 1.0 0.1 0.95

#define MILD_DIM_GREEN_COLOR    0.2 0.7490 0.2 0.8
#define DIM_GREEN_COLOR     0.0 1   0.6 0.4
#define DIM_BLUE_COLOR      0.0 0.6 1   0.9
#define DIM_GREY_COLOR      0.3 0.3 0.3 0.65
#define DIM_COLOR           0.2 0.2 0.2 0.65
#define HEADER_COLOR        PERIWINKLE_COLOR

#define OPENCJ_UI_DVAR_PREFIX       "opencj_ui_"
#define OPENCJDVAR(_dvar)            OPENCJ_UI_DVAR_PREFIX _dvar

#define FULLSCREEN_X                640
#define FULLSCREEN_Y                480

#define LEADERBOARD_ORG_X           0
#define LEADERBOARD_ORG_Y           120
#define LEADERBOARD_SIZE_X          (FULLSCREEN_X-LEADERBOARD_ORG_X-75)
#define LEADERBOARD_SIZE_Y          (FULLSCREEN_Y-LEADERBOARD_ORG_Y-140)

#define LEFT_FRAME_SIZE_X         (250 / 2)
#define LEFT_FRAME_SIZE_Y         (OUTER_FRAME_SIZE_Y - (2 * ELEMENT_SPACING))
#define LEFT_FRAME_ORG_X          OUTER_FRAME_ORG_X
#define LEFT_FRAME_ORG_Y          OUTER_FRAME_ORG_Y

    // LB pages
#define MAIN_CONTENT_X          (OUTER_FRAME_ORG_X + MR_CELL_SIZE_X + 18)
#define MAIN_CONTENT_Y          (OUTER_FRAME_ORG_Y + H_SEP_ORG_Y + (10 * 2) - 8)
#define MAIN_CONTENT_X_SIZE     458
#define MAIN_CONTENT_Y_SIZE     195


#define BUTTON_RECT_BASE(_name, _font, _backColor, _foreColor, _txtScale, orgX, orgY, sizeX, sizeY) \
    name            _name \
    style           WINDOW_STYLE_FILLED \
    rect            DEFAULT_RECT(0 0 sizeX sizeY) \
    origin          orgX orgY \
    backcolor       _backColor \
    foreColor       _foreColor \
    type            ITEM_TYPE_BUTTON \
    textfont        _font \
    textscale       _txtScale \
    textalign       ITEM_ALIGN_MIDDLE_CENTER \
    visible         1

#define BUTTON_RECT_BORDER_BASE(_name, _font, _backColor, _foreColor, _txtScale, orgX, orgY, sizeX, sizeY, _borderColor, _borderSize) \
    name            _name \
    style           WINDOW_STYLE_FILLED \
    rect            DEFAULT_RECT(0 0 (sizeX+2) (sizeY+2)) \
    origin          (orgX-2) (orgY-2) \
    backcolor       _backColor \
    foreColor       _foreColor \
    type            ITEM_TYPE_BUTTON \
    textfont        _font \
    textscale       _txtScale \
    textalign       ITEM_ALIGN_MIDDLE_CENTER \
    visible         1 \
    border          WINDOW_BORDER_FULL \
    bordercolor     _borderColor \
    bordersize      _borderSize \
    mouseEnter      { setitemcolor _name bordercolor HIGHLIGHT_COLOR; play "mouse_over" } \
    mouseExit       { setitemcolor _name bordercolor _borderColor }

#define BUTTON_RECT_ACTIONBASE(_name, _font, _extraAction, _backColor, _foreColor, _txtScale, orgX, orgY, sizeX, sizeY) \
    BUTTON_RECT_BASE(_name, _font, _backColor, _foreColor, _txtScale, orgX, orgY, sizeX, sizeY) \
    action          { play "mouse_click"; scriptMenuResponse "click_"#_name; _extraAction }

#define BUTTON_RECT_BORDER_ACTIONBASE(_name, _font, _extraAction, _backColor, _foreColor, _txtScale, orgX, orgY, sizeX, sizeY, _borderColor, _borderSize) \
    BUTTON_RECT_BORDER_BASE(_name, _font, _backColor, _foreColor, _txtScale, orgX, orgY, sizeX, sizeY, _borderColor, _borderSize) \
    action          { play "mouse_click"; scriptMenuResponse "click_"#_name; _extraAction }


#define BUTTON_RECT_DVAR(_name, _dvar, _backColor, _foreColor, _font, _txtScale, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        BUTTON_RECT_ACTIONBASE(_name, _font, "", _backColor, _foreColor, _txtScale, orgX, orgY, sizeX, sizeY) \
        dvar            _dvar \
        dvartest        _dvar \
        hidedvar        { "" } \
    }

#define BUTTON_RECT_DVAR_WHEN(_name, _dvar, _visibility, _backColor, _foreColor, _font, _txtScale, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        BUTTON_RECT_ACTIONBASE(_name, _font, "", _backColor, _foreColor, _txtScale, orgX, orgY, sizeX, sizeY) \
        dvar            _dvar \
        dvartest        _dvar \
        hidedvar        { "" } \
        visible         when( _visibility ) \
    }

#define BUTTON_RECT_TXT(_name, _text, _onAction, _backColor, _foreColor, _font, _txtScale, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        BUTTON_RECT_ACTIONBASE(_name, _font, _onAction, _backColor, _foreColor, _txtScale, orgX, orgY, sizeX, sizeY) \
        text            _text \
    }

#define BUTTON_RECT_BORDER_TXT(_name, _text, _onAction, _backColor, _foreColor, _font, _txtScale, orgX, orgY, sizeX, sizeY, _borderColor, _borderSize) \
    itemDef \
    { \
        BUTTON_RECT_BORDER_ACTIONBASE(_name, _font, _onAction, _backColor, _foreColor, _txtScale, orgX, orgY, sizeX, sizeY, _borderColor, _borderSize) \
        text            _text \
    }

#define BUTTON_RECT_TXT_ACTION(_name, _text, _action, _backColor, _foreColor, _font, _txtScale, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        BUTTON_RECT_BASE(_name, _font, _backColor, _foreColor, _txtScale, orgX, orgY, sizeX, sizeY) \
        action          { _action } \
        text            _text \
    }

#define SORTABLE_RECT(_name, _text, _color, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        name        _name \
        type        ITEM_TYPE_BUTTON \
        style       WINDOW_STYLE_FILLED \
        rect        DEFAULT_RECT(0 0 sizeX sizeY) \
        origin      orgX orgY \
        forecolor   WHITE_COLOR \
        backcolor   _color \
        text        _text \
        textfont    UI_FONT_NORMAL \
        textscale   0.25 \
        textalignx  3 \
        textaligny  14 \
        visible     1 \
        mouseEnter  { play "mouse_over" } \
        action      { scriptMenuResponse "click_"#_name; play "mouse_click" } \
    }

#define SHADER_RECT_BASE(_name, _shader, orgX, orgY, sizeX, sizeY) \
    name        _name \
    style       WINDOW_STYLE_SHADER \
    background  _shader \
    rect        DEFAULT_RECT(0 0 sizeX sizeY) \
    origin      orgX orgY

#define SEL_SHADER_RECT_BASE(_name, _extraAction, _shader, orgX, orgY, sizeX, sizeY) \
    SHADER_RECT_BASE(_name, _shader, orgX, orgY, sizeX, sizeY) \
    type        ITEM_TYPE_BUTTON \
    action      { scriptMenuResponse "click_"#_name; play "mouse_click"; _extraAction } \
    mouseEnter  { play "mouse_over" }

#define SEL_SHADER_RECT_ALWAYS(_name, _shader, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        SEL_SHADER_RECT_BASE(_name, "", _shader, orgX, orgY, sizeX, sizeY) \
        visible 1 \
    }

#define SEL_SHADER_RECT_ALWAYS_ACTION(_name, _extraAction, _shader, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        SEL_SHADER_RECT_BASE(_name, _extraAction, _shader, orgX, orgY, sizeX, sizeY) \
        visible 1 \
    }

#define SEL_SHADER_RECT_WHEN(_name, _shader, _foreColor, _visibility, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        SEL_SHADER_RECT_BASE(_name, "", _shader, orgX, orgY, sizeX, sizeY) \
        forecolor   _foreColor \
        visible     when( _visibility ) \
    }

#define SEL_DVARSHADER_RECT(_name, _dvar, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        name        _name \
        style       WINDOW_STYLE_DVAR_SHADER \
        type        ITEM_TYPE_BUTTON \
        rect        DEFAULT_RECT(0 0 sizeX sizeY) \
        origin      orgX orgY \
        dvar        _dvar \
        visible     1 \
        action      { play "mouse_click"; scriptMenuResponse "click_"#_name } \
        onFocus     { play "mouse_over" } \
    }

#define SHADER_RECT_WHEN(_name, _shader, _visibility, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        SHADER_RECT_BASE(_name, _shader, orgX, orgY, sizeX, sizeY) \
        visible     when( _visibility ) \
    }

#define SHADER_RECT_ALWAYS(_name, _shader, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        SHADER_RECT_BASE(_name, _shader, orgX, orgY, sizeX, sizeY) \
        visible     1 \
    }

#define DROPDOWN_RECT(_menu, _text, _font, _color, orgX, orgY, sizeX, sizeY) \
        itemDef \
        { \
            style       WINDOW_STYLE_FILLED \
            rect        DEFAULT_RECT(0 0 sizeX sizeY) \
            origin      orgX orgY \
            visible     MENU_TRUE \
            backcolor   _color \
            forecolor   WHITE_COLOR \
            type        ITEM_TYPE_BUTTON \
            textfont    _font \
            textscale   0.25 \
            textalignx  3 \
            textaligny  14 \
            text        _text \
            mouseEnter  { play "mouse_over" } \
            action      { play "mouse_click"; open _menu } \
        }

#define FIXED_RECT_BASE(_backColor, orgX, orgY, sizeX, sizeY) \
    style       WINDOW_STYLE_FILLED \
    rect        DEFAULT_RECT(0 0 sizeX sizeY) \
    origin      orgX orgY \
    backcolor   _backColor \
    decoration

#define FIXED_RECT_BASE_BORDER(_backColor, _borderSize, _borderColor, orgX, orgY, sizeX, sizeY) \
    style       WINDOW_STYLE_FILLED \
    rect        DEFAULT_RECT(0 0 sizeX sizeY) \
    origin      orgX orgY \
    backcolor   _backColor \
    border      WINDOW_BORDER_FULL \
    bordercolor _borderColor \
    bordersize  _borderSize \
    decoration

#define FIXED_RECT_TEXT_BASE(_font, _txtStyle, _txtScale, _txtAlign, _txtAlignX, _txtAlignY, _backColor, _foreColor, orgX, orgY, sizeX, sizeY) \
    FIXED_RECT_BASE(_backColor, orgX, orgY, sizeX, sizeY) \
    type        ITEM_TYPE_TEXT \
    forecolor   _foreColor \
    textfont    _font \
    textscale   _txtScale \
    textalign   _txtAlign \
    textalignx  _txtAlignX \
    textaligny  _txtAlignY \
    textstyle   _txtStyle \

#define FIXED_RECT(_backColor, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        FIXED_RECT_BASE(_backColor, orgX, orgY, sizeX, sizeY) \
        visible     1 \
    }

#define FIXED_RECT_BORDER(_backColor, _borderSize, _borderColor, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        FIXED_RECT_BASE_BORDER(_backColor, _borderSize, _borderColor, orgX, orgY, sizeX, sizeY) \
        visible     1 \
    }


#define FIXED_RECT_WHEN(_visibility, _backColor, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        FIXED_RECT_BASE(_backColor, orgX, orgY, sizeX, sizeY) \
        visible     when( _visibility ) \
    }

#define FIXED_RECT_OUTLINE_SHOW(_dvar, _showDvar, _focusBorderColor, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        FIXED_RECT_BASE(NO_COLOR, orgX, orgY, sizeX, sizeY) \
        dvartest    _dvar \
        showdvar    { _showDvar } \
        visible     1 \
        border      WINDOW_BORDER_FULL \
        bordercolor _focusBorderColor \
        bordersize  1 \
    }

#define FIXED_RECT_OUTLINE_HIDE(_name, _dvar, _hideDvar, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        FIXED_RECT_BASE(NO_COLOR, orgX, orgY, sizeX, sizeY) \
        name _name \
        dvartest    _dvar \
        hidedvar    { _hideDvar } \
        visible     1 \
        border      WINDOW_BORDER_FULL \
        bordercolor NO_COLOR \
        bordersize  1 \
        mouseEnter  { setitemcolor _name bordercolor LIGHTGREY_COLOR } \
        mouseExit   { setitemcolor _name bordercolor NO_COLOR } \
    }

#define FIXED_RECT_DVAR(_dvar, _font, _txtStyle, _txtScale, _txtAlign, _txtAlignX, _txtAlignY, _backColor, _foreColor, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        FIXED_RECT_TEXT_BASE(_font, _txtStyle, _txtScale, _txtAlign, _txtAlignX, _txtAlignY, _backColor, _foreColor, orgX, orgY, sizeX, sizeY) \
        dvar _dvar \
        visible when (dvarString(_dvar) != "") \
    }

#define FIXED_RECT_TXT(_visibility, _text, _font, _txtStyle, _txtScale, _txtAlign, _txtAlignX, _txtAlignY, _backColor, _foreColor, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        FIXED_RECT_TEXT_BASE(_font, _txtStyle, _txtScale, _txtAlign, _txtAlignX, _txtAlignY, _backColor, _foreColor, orgX, orgY, sizeX, sizeY) \
        text _text \
        visible _visibility \
    }

#define FIXED_RECT_DVARLEFT(_dvar, _backColor, _foreColor, orgX, orgY, sizeX, sizeY) \
    FIXED_RECT_DVAR(_dvar, UI_FONT_NORMAL, ITEM_TEXTSTYLE_NORMAL, 0.20, ITEM_ALIGN_MIDDLE_LEFT, 3, 0, _backColor, _foreColor, orgX, orgY, sizeX, sizeY)

#define FIXED_RECT_DVARLEFT_SCALED(_dvar, _backColor, _foreColor, _txtScale, orgX, orgY, sizeX, sizeY) \
    FIXED_RECT_DVAR(_dvar, UI_FONT_NORMAL, ITEM_TEXTSTYLE_NORMAL, _txtScale, ITEM_ALIGN_MIDDLE_LEFT, 5, 0, _backColor, _foreColor, orgX, orgY, sizeX, sizeY)

#define FIXED_RECT_DVARLEFT_SCALED_BLINK(_dvar, _backColor, _foreColor, _txtScale, orgX, orgY, sizeX, sizeY) \
    FIXED_RECT_DVAR(_dvar, UI_FONT_NORMAL, ITEM_TEXTSTYLE_BLINK, _txtScale, ITEM_ALIGN_MIDDLE_LEFT, 5, 0, _backColor, _foreColor, orgX, orgY, sizeX, sizeY)

#define FIXED_RECT_DVARLEFT_STYLED(_dvar, _font, _txtScale, _backColor, _foreColor, orgX, orgY, sizeX, sizeY) \
    FIXED_RECT_DVAR(_dvar, _font, ITEM_TEXTSTYLE_SHADOWED, _txtScale, ITEM_ALIGN_MIDDLE_LEFT, 0, 0, _backColor, _foreColor, orgX, orgY, sizeX, sizeY)

#define FIXED_RECT_DVARCENTER(_dvar, _backColor, _foreColor, orgX, orgY, sizeX, sizeY) \
    FIXED_RECT_DVAR(_dvar, UI_FONT_NORMAL, ITEM_TEXTSTYLE_NORMAL, 0.20, ITEM_ALIGN_MIDDLE_CENTER, 0, 0, _backColor, _foreColor, orgX, orgY, sizeX, sizeY)

#define FIXED_RECT_DVARCENTER_SCALED(_dvar, _backColor, _foreColor, _txtScale, orgX, orgY, sizeX, sizeY) \
    FIXED_RECT_DVAR(_dvar, UI_FONT_NORMAL, ITEM_TEXTSTYLE_NORMAL, _txtScale, ITEM_ALIGN_MIDDLE_CENTER, 0, 0, _backColor, _foreColor, orgX, orgY, sizeX, sizeY)

#define FIXED_RECT_DVARRIGHT(_dvar, _backColor, _foreColor, orgX, orgY, sizeX, sizeY) \
    FIXED_RECT_DVAR(_dvar, UI_FONT_NORMAL, ITEM_TEXTSTYLE_NORMAL, 0.20, ITEM_ALIGN_MIDDLE_RIGHT, -5, 0, _backColor, _foreColor, orgX, orgY, sizeX, sizeY)

#define FIXED_RECT_DVARRIGHT_SCALED(_dvar, _backColor, _foreColor, _txtScale, orgX, orgY, sizeX, sizeY) \
    FIXED_RECT_DVAR(_dvar, UI_FONT_NORMAL, ITEM_TEXTSTYLE_NORMAL, _txtScale, ITEM_ALIGN_MIDDLE_RIGHT, -5, 0, _backColor, _foreColor, orgX, orgY, sizeX, sizeY)

#define FIXED_RECT_DVARCENTER_STYLED(_dvar, _txtScale, _backColor, _foreColor, orgX, orgY, sizeX, sizeY) \
    FIXED_RECT_DVAR(_dvar, UI_FONT_DEFAULT, ITEM_TEXTSTYLE_SHADOWED, _txtScale, ITEM_ALIGN_MIDDLE_CENTER, 0, 0, _backColor, _foreColor, orgX, orgY, sizeX, sizeY)

#define FIXED_RECT_DVARCENTER_STYLED_WHEN(_dvar, _visibility, _txtScale, _backColor, _foreColor, orgX, orgY, sizeX, sizeY) \
    itemDef \
    { \
        FIXED_RECT_TEXT_BASE(UI_FONT_DEFAULT, ITEM_TEXTSTYLE_SHADOWEDMORE, _txtScale, ITEM_ALIGN_MIDDLE_CENTER, 0, 0, _backColor, _foreColor, orgX, orgY, sizeX, sizeY) \
        dvar _dvar \
        visible when ( _visibility ) \
    }

#define FIXED_RECT_TXTLEFT(_text, _backColor, _foreColor, orgX, orgY, sizeX, sizeY) \
    FIXED_RECT_TXT(1, _text, UI_FONT_NORMAL, ITEM_TEXTSTYLE_NORMAL, 0.20, ITEM_ALIGN_MIDDLE_LEFT, 5, 0, _backColor, _foreColor, orgX, orgY, sizeX, sizeY)

#define FIXED_RECT_TXTLEFT_SCALED(_text, _txtScale, _backColor, _foreColor, orgX, orgY, sizeX, sizeY) \
    FIXED_RECT_TXT(1, _text, UI_FONT_NORMAL, ITEM_TEXTSTYLE_NORMAL, _txtScale, ITEM_ALIGN_MIDDLE_LEFT, 10, 0, _backColor, _foreColor, orgX, orgY, sizeX, sizeY)

#define FIXED_RECT_TXTCENTER(_text, _backColor, _foreColor, orgX, orgY, sizeX, sizeY) \
    FIXED_RECT_TXT(1, _text, UI_FONT_NORMAL, ITEM_TEXTSTYLE_NORMAL, 0.20, ITEM_ALIGN_MIDDLE_CENTER, 0, 0, _backColor, _foreColor, orgX, orgY, sizeX, sizeY)

#define FIXED_RECT_TXTRIGHT(_text, _backColor, _foreColor, orgX, orgY, sizeX, sizeY) \
    FIXED_RECT_TXT(1, _text, UI_FONT_NORMAL, ITEM_TEXTSTYLE_NORMAL, 0.20, ITEM_ALIGN_MIDDLE_RIGHT, -5, 0, _backColor, _foreColor, orgX, orgY, sizeX, sizeY)

#define FIXED_RECT_TXTCENTER_WHEN(_visibility, _text, _backColor, _foreColor, orgX, orgY, sizeX, sizeY) \
    FIXED_RECT_TXT(when ( _visibility ), _text, UI_FONT_NORMAL, ITEM_TEXTSTYLE_NORMAL, 0.24, ITEM_ALIGN_MIDDLE_CENTER, 0, 0, _backColor, _foreColor, orgX, orgY, sizeX, sizeY)

#define FIXED_RECT_TXTCENTER_STYLED_WHEN(_visibility, _text, _txtScale, _backColor, _foreColor, orgX, orgY, sizeX, sizeY) \
    FIXED_RECT_TXT(when( _visibility), _text, UI_FONT_NORMAL, ITEM_TEXTSTYLE_SHADOWEDMORE, _txtScale, ITEM_ALIGN_MIDDLE_CENTER, 0, 0, _backColor, _foreColor, orgX, orgY, sizeX, sizeY)
