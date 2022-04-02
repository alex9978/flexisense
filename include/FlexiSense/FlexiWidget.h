
/*! @class FlexiWidget
 *  @brief Base element for the gui
 *  @author Alessandro Rasulo (mailto: alex9978@gmail.com)
 */

#ifndef FLEXIWIDGET_H
#define FLEXIWIDGET_H

#include <FlexiSense/common/FlexiColor.h>
#include <FlexiSense/common/FlexiDefines.h>
#include <FlexiSense/common/FlexiGridBag.h>
#include <FlexiSense/common/FlexiImage.h>
#include <FlexiSense/common/FlexiPosition.h>
#include <FlexiSense/common/FlexiSize.h>
#include <FlexiSense/common/FlexiTheme.h>
#include <FlexiSense/listeners/FlexiActionListener.h>
#include <FlexiSense/listeners/FlexiFocusListener.h>
#include <FlexiSense/listeners/FlexiKeyListener.h>
#include <FlexiSense/listeners/FlexiMouseListener.h>
#include <FlexiSense/sensitiveAreas/FlexiSensitiveArea.h>

#include <list>
#include <string>
#include <vector>

class FLX_EXPORT FlexiWidget : public FlexiObject
{
public:
    FlexiWidget                             (const FlexiPosition &p, const FlexiSize &s, FlexiWidget *prnt);
    virtual ~FlexiWidget                    ();

    // Name
    void setName                            (const std::string &newName);
    const std::string &getName              () const;

    // Parent
    FlexiWidget *getParent                  ();
    bool reparent                           (FlexiWidget *newParent);
    bool isContainer                        ();
    
    // Children
    void addChild                           (FlexiWidget *child);
    const std::list<FlexiWidget *> getChildren() const;
    
    // Properties
    const FlexiPosition &getPosition        ();
    const FlexiSize &getSize                ();
    const FlexiPosition &getAbsPosition     ();
    const FlexiPosition &getOriginalPosition();
    
    virtual void resize                     (const FlexiPosition &p, const FlexiSize &s);   
    void setPosition                        (const FlexiPosition &p);
    void setSize                            (const FlexiSize &s);

    void show                               ();
    void hide                               ();
    void activate                           ();
    void deactivate                         ();
    bool isVisible                          ();
    bool isActive                           ();
    
    void setFocusable                       (bool focusable);
    void setFocus                           ();
    bool isFocusable                        ();
    bool isFocused                          ();

    void setHilighted                       (bool hilight);
    bool isHilighted                        ();

    // Event dispatchers
    void dispatchFocusEvent                 (FlexiFocusEvent *event);
    void dispatchMouseEvent                 (FlexiMouseEvent *event);
    
    // Flags
    void setFlags                           (int flags, bool value);
    bool getFlags                           (int flags);

    // Colors
    FlexiColor                              backColor;
    FlexiColor                              foreColor;
    FlexiColor                              inactiveColor;
    FlexiColor                              selectionColor;
    FlexiColor                              pressedColor;

    // Back image
    void setBackImage                       (FlexiImage *image, int gridBagType = FlexiGridBag::FLX_GRIDBAG_1X1);

    // UI Zone
    bool setSensitiveArea                   (FlexiSensitiveArea *sensitive_area);
    bool isMouseOver                        (int mouseX, int mouseY);

    // Tag
    void setTag                             (long value);
    long getTag                             ();

    // Event listeners
    void addActionListener                  (FlexiActionListener    *listener);
    void addFocusListener                   (FlexiFocusListener     *listener);
    void addKeyListener                     (FlexiKeyListener       *listener);
    void addMouseListener                   (FlexiMouseListener     *listener);

    void addUserActionListener              (FlexiActionListener    *listener);
    void addUserFocusListener               (FlexiFocusListener     *listener);
    void addUserKeyListener                 (FlexiKeyListener       *listener);
    void addUserMouseListener               (FlexiMouseListener     *listener);

    void callActionListener                 (FlexiActionEvent       *event);
    void callFocusListener                  (FlexiFocusEvent        *event);
    void callKeyListener                    (FlexiKeyEvent          *event);
    void callMouseListener                  (FlexiMouseEvent        *event);

    // Paint
    virtual void paint                      ();
    
protected:    
    std::string                             name;
    bool                                    container;    
    FlexiWidget             			   *parent;
    std::list<FlexiWidget *>                children;
    
    // properties
    FlexiPosition                           position,				// properties
                                            absolutePosition,
                                            originalPosition;
    FlexiSize                               size;
    bool                                    visible,
                                            active,
                                            focusable,
                                            focused,
                                            hilighted;

	int                                     flags;					// flags

	FlexiImage                             *backImage;				// images
	int                                     gridBagType;

	FlexiSensitiveArea                     *area;					// sensitive area

	long                                    tag;					// tag (user data)

	FlexiActionListener                    *actionListener;         // default listeners
    FlexiFocusListener                     *focusListener;
	FlexiKeyListener                       *keyListener;
	FlexiMouseListener                     *mouseListener;

	FlexiActionListener                    *userActionListener;     // user listeners
    FlexiFocusListener                     *userFocusListener;
	FlexiKeyListener                       *userKeyListener;
	FlexiMouseListener                     *userMouseListener;
};

#endif // FLEXIWIDGET_H
