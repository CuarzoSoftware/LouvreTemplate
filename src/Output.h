#ifndef OUTPUT_H
#define OUTPUT_H

#include <LOutput.h>
#include <LSolidColorView.h>

class Surface;

using namespace Louvre;

/* The graphic backend creates an instance of this class for each available
 * display (laptop screen, HDMI display, etc.).
 *
 * All outputs are initially uninitialized. To initialize/uninitialize an output, use
 * LCompositor::addOutput()/removeOutput(). See Compositor::initialized().
 *
 * All available outputs can be accessed through LSeat::outputs(), and only the initialized ones
 * from LCompositor::outputs().
 *
 * Outputs can also be hot-plugged, see Seat::outputPlugged()/outputUnplugged() for more details.
 *
 * When initialized, a new rendering thread is created from which the xxxGL() events are triggered.
 * OpenGL rendering must only be performed within a paintGL() event and nowhere else.
 * The rendering thread blocks until repaint() is called, which later triggers the paintGL() event.
 * Calling repaint() multiple times only unlocks the rendering thread once, so within or after a
 * paintGL() event, repaint() must be called again to unlock the thread once more.
 *
 * Note: When views or surfaces change, they typically call repaint() automatically on the outputs
 * where they are visible. However, there are cases where it must be called manually.
 * See LCompositor::repaintAllOutputs(), LSurface::repaintOutputs(), and LView::repaint().
 */
class Output final : public LOutput
{
public:
    using LOutput::LOutput;

    /* Here you can initialize OpenGL ES 2.0 rendering toolkits, shaders, etc., if needed,
     * or use the painter() utility. We use LScene instead, which efficiently renders views for you,
     * repainting only damaged areas, preventing rendering of content behind opaque surfaces, etc.
     */
    void initializeGL() override;

    /* This is the only place where you should perform painting operations, which will be displayed
     * on the screen after the backend performs a page flip. Again, LScene handles this for you,
     * you only need to properly position, configure, and arrange your views.
     */
    void paintGL() override;

    /* Outputs, like views and surfaces, are positioned within the compositor-global coordinate space.
     * This event is triggered asynchronously after you change the output position with setPos().
     * Think of pos() and size() as the portion of the global compositor space that the output is
     * "capturing" and displaying to the screen.
     */
    void moveGL() override;

    /* This is triggered when the output size changes, for example, after changing its currentMode()
     * or when adjusting the scale().
     */
    void resizeGL() override;

    /* This is triggered after the output is removed from the compositor (LCompositor::removeOutput())
     * or when it is unplugged (Seat::outputUnplugged()).
     * Note: After this, the rendering thread is destroyed, use this instance to free any output-specific
     * resources you may have created.
     */
    void uninitializeGL() override;

    void setGammaRequest(LClient *client, const LGammaTable *gamma) override;
    void availableGeometryChanged() override;

    /* For the example fade-in animation */
    LSolidColorView fadeInView { {0.f, 0.f, 0.f } };

    Surface *searchFullscreenSurface() const noexcept;
    bool tryDirectScanout(Surface *surface) noexcept;
};

#endif // OUTPUT_H
