
#include "ListenerHelper.h"
#include "MyProtocolHandler.h"

#include <com/sun/star/awt/MessageBoxButtons.hpp>
#include <com/sun/star/awt/Toolkit.hpp>
#include <com/sun/star/awt/XMessageBoxFactory.hpp>
#include <com/sun/star/frame/ControlCommand.hpp>
#include <com/sun/star/text/XTextViewCursorSupplier.hpp>
#include <com/sun/star/sheet/XSpreadsheetView.hpp>
#include <com/sun/star/system/SystemShellExecute.hpp>
#include <com/sun/star/system/SystemShellExecuteFlags.hpp>
#include <com/sun/star/system/XSystemShellExecute.hpp>
#include <cppuhelper/supportsservice.hxx>
#include <com/sun/star/text/XTextDocument.hpp>
#include <com/sun/star/text/XText.hpp>
#include <com/sun/star/text/XTextCursor.hpp>
#include <com/sun/star/lang/XComponent.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>

using namespace com::sun::star::awt;
using namespace com::sun::star::frame;
using namespace com::sun::star::system;
using namespace com::sun::star::uno;

using com::sun::star::beans::NamedValue;
using com::sun::star::beans::PropertyValue;
using com::sun::star::sheet::XSpreadsheetView;
using com::sun::star::text::XTextViewCursorSupplier;
using com::sun::star::util::URL;
using com::sun::star::text::XText;
using com::sun::star::text::XTextCursor;
using com::sun::star::text::XTextDocument;
using com::sun::star::lang::XComponent;
using com::sun::star::frame::XComponentLoader;
using ::rtl::OUString;

ListenerHelper aListenerHelper;

void 
BaseDispatch::ShowMessageBox(
    const Reference<XFrame> &rFrame, 
    const ::rtl::OUString &aTitle, 
    const ::rtl::OUString &aMsgText
) {
    if (!mxToolkit.is())
        mxToolkit = Toolkit::create(mxContext);
    Reference<XMessageBoxFactory> xMsgBoxFactory(mxToolkit, UNO_QUERY);
    if (rFrame.is() && xMsgBoxFactory.is())
    {
        Reference<XMessageBox> xMsgBox = xMsgBoxFactory->createMessageBox(
            Reference<XWindowPeer>(rFrame->getContainerWindow(), UNO_QUERY),
            com::sun::star::awt::MessageBoxType_INFOBOX,
            MessageBoxButtons::BUTTONS_OK,
            aTitle,
            aMsgText);

        if (xMsgBox.is())
            xMsgBox->execute();
    }
}

void 
BaseDispatch::SendCommand(
    const com::sun::star::util::URL &aURL, 
    const ::rtl::OUString &rCommand, 
    const Sequence<NamedValue> &rArgs, 
    sal_Bool bEnabled
) {
    Reference<XDispatch> xDispatch =
        aListenerHelper.GetDispatch(mxFrame, aURL.Path);

    FeatureStateEvent aEvent;

    aEvent.FeatureURL = aURL;
    aEvent.Source = xDispatch;
    aEvent.IsEnabled = bEnabled;
    aEvent.Requery = sal_False;

    ControlCommand aCtrlCmd;
    aCtrlCmd.Command = rCommand;
    aCtrlCmd.Arguments = rArgs;

    aEvent.State <<= aCtrlCmd;
    aListenerHelper.Notify(mxFrame, aEvent.FeatureURL.Path, aEvent);
}

void 
BaseDispatch::SendCommandTo(
    const Reference<XStatusListener> &xControl, 
    const URL &aURL, 
    const ::rtl::OUString &rCommand, 
    const Sequence<NamedValue> &rArgs, 
    sal_Bool bEnabled
) {
    FeatureStateEvent aEvent;

    aEvent.FeatureURL = aURL;
    aEvent.Source = (::com::sun::star::frame::XDispatch *)this;
    aEvent.IsEnabled = bEnabled;
    aEvent.Requery = sal_False;

    ControlCommand aCtrlCmd;
    aCtrlCmd.Command = rCommand;
    aCtrlCmd.Arguments = rArgs;

    aEvent.State <<= aCtrlCmd;
    xControl->statusChanged(aEvent);
}

void SAL_CALL 
MyProtocolHandler::initialize(
    const Sequence<Any> &aArguments
) {
    Reference<XFrame> xFrame;
    if (aArguments.getLength())
    {
        // the first Argument is always the Frame, as a ProtocolHandler needs to have access
        // to the context in which it is invoked.
        aArguments[0] >>= xFrame;
        mxFrame = xFrame;
    }
}

Reference<XDispatch> SAL_CALL 
MyProtocolHandler::queryDispatch(
    const URL &aURL, 
    const ::rtl::OUString &sTargetFrameName, 
    sal_Int32 nSearchFlags
) {
    Reference<XDispatch> xRet;
    if (!mxFrame.is())
        return 0;

    Reference<XController> xCtrl = mxFrame->getController();
    if (xCtrl.is() && aURL.Protocol == "vnd.demo.complextoolbarcontrols.demoaddon:")
    {
        Reference<XTextViewCursorSupplier> xCursor(xCtrl, UNO_QUERY);
        Reference<XSpreadsheetView> xView(xCtrl, UNO_QUERY);
        if (!xCursor.is() && !xView.is())
            // without an appropriate corresponding document the handler doesn't function
            return xRet;

        if (aURL.Path == "spinWordCount" ||
            aURL.Path == "setWordLanguage" ||
            aURL.Path == "setMaxWordLength" ||
            aURL.Path == "generateText" ||
            aURL.Path == "appendStatistics" ||
            aURL.Path == "colorCyrilics")
        {
            xRet = aListenerHelper.GetDispatch(mxFrame, aURL.Path);
            if (!xRet.is())
            {
                xRet = (BaseDispatch *)new WriterDispatch(mxContext, mxFrame);
                aListenerHelper.AddDispatch(xRet, mxFrame, aURL.Path);
            }
        }
    }

    return xRet;
}

Sequence<Reference<XDispatch>> SAL_CALL 
MyProtocolHandler::queryDispatches(
    const Sequence<DispatchDescriptor> &seqDescripts
) {
    sal_Int32 nCount = seqDescripts.getLength();
    Sequence<Reference<XDispatch>> lDispatcher(nCount);

    for (sal_Int32 i = 0; i < nCount; ++i)
        lDispatcher[i] = queryDispatch(seqDescripts[i].FeatureURL, seqDescripts[i].FrameName, seqDescripts[i].SearchFlags);

    return lDispatcher;
}

::rtl::OUString 
MyProtocolHandler_getImplementationName(
) {
    return ::rtl::OUString(MYPROTOCOLHANDLER_IMPLEMENTATIONNAME);
}

Sequence<::rtl::OUString> SAL_CALL 
MyProtocolHandler_getSupportedServiceNames(
) {
    Sequence<::rtl::OUString> aRet(1);
    aRet[0] = ::rtl::OUString(MYPROTOCOLHANDLER_SERVICENAME);
    return aRet;
}

#undef SERVICE_NAME

Reference<XInterface> SAL_CALL 
MyProtocolHandler_createInstance(
    const Reference<XComponentContext> &rSMgr
) {
    return (cppu::OWeakObject *)new MyProtocolHandler(rSMgr);
}

// XServiceInfo
::rtl::OUString SAL_CALL 
MyProtocolHandler::getImplementationName(
) {
    return MyProtocolHandler_getImplementationName();
}

sal_Bool SAL_CALL 
MyProtocolHandler::supportsService(
    const ::rtl::OUString &rServiceName
) {
    return cppu::supportsService(this, rServiceName);
}

Sequence<::rtl::OUString> SAL_CALL 
MyProtocolHandler::getSupportedServiceNames(
) {
    return MyProtocolHandler_getSupportedServiceNames();
}






#define RTL_TEXTENCODING_UTF8   (RTL_TEXTENC_CAST( 76 ))
enum class GenLang {
    Russian,
    English,
    Any,
};

const char* RU_CHAR = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
OUString RU(RU_CHAR, strlen(RU_CHAR), RTL_TEXTENCODING_UTF8);
OUString EN = "abcdefghijklmnopqrstuvwxyz";
OUString ANY = RU + EN;

OUString generateWord(const int& maxLen, const GenLang& genLang) {
    OUString alphabet = EN;
    if (genLang == GenLang::Russian) alphabet = RU;
    if (genLang == GenLang::Any) alphabet = ANY;
    int alphabetLen = alphabet.getLength();
    int len = rand() % maxLen;
    if (len == 0) len = 1;
    
    OUString result = "";
    for (int i = 0; i < len; ++i) {
        result += alphabet.copy(rand() % alphabetLen, 1);
    }
    return result;
}

OUString generateText(const int& wordCount, const int& maxWordLen, const GenLang& genLang) {
    OUString result = "";

    for (int word_i = 0; word_i < wordCount; ++word_i) {
        result += generateWord(maxWordLen, genLang) + " ";
    }

    return result;
}





void SAL_CALL 
BaseDispatch::dispatch(
    const URL &aURL, 
    const Sequence<PropertyValue> &lArgs
) {
    /* It's necessary to hold this object alive, till this method finishes.
       May the outside dispatch cache (implemented by the menu/toolbar!)
       forget this instance during de-/activation of frames (focus!).

        E.g. An open db beamer in combination with the My-Dialog
        can force such strange situation :-(
     */
    Reference<XInterface> xSelfHold(static_cast<XDispatch *>(this), UNO_QUERY);

    if (aURL.Protocol == "vnd.demo.complextoolbarcontrols.demoaddon:")
    {
        if (aURL.Path == "generateText") {
            Reference < XComponentLoader > rComponentLoader(
                this->mxFrame, 
                UNO_QUERY
            );
            Reference <XComponent> xWriterComponent = rComponentLoader -> loadComponentFromURL(
                OUString::createFromAscii("private:factory/swriter"),
                OUString::createFromAscii("_blank"),
                0,
                Sequence < ::com::sun::star::beans::PropertyValue > ()
            );
            Reference < XTextDocument > xTextDocument(
                xWriterComponent, 
                UNO_QUERY
            );
            Reference < XText > xText = xTextDocument -> getText();
            Reference < XTextCursor > xTextCursor = xText -> createTextCursor();
            
            GenLang genLang = 
                this->langType == 0 
                ? GenLang::English 
                : this->langType == 1
                ? GenLang::Russian
                : GenLang::Any;
            xText -> insertString(xTextCursor, generateText(this->wordCount, this->maxWordLen, genLang), false);
        } else if (aURL.Path == "setMaxWordLength") {
            // Retrieve the text argument from the sequence property value
            rtl::OUString aText;
            for (sal_Int32 i = 0; i < lArgs.getLength(); i++)
            {
                if (lArgs[i].Name == "Text")
                {
                    lArgs[i].Value >>= aText;
                    break;
                }
            }
            try {
                this->maxWordLen = aText.toInt32();
            } catch (Exception &ex) {
                ShowMessageBox(this->mxFrame, "maxWordLen", "wrong");
            }
        } else if (aURL.Path == "setWordLanguage") {
            rtl::OUString aText;
            for (sal_Int32 i = 0; i < lArgs.getLength(); i++)
            {
                if (lArgs[i].Name == "Text")
                {
                    lArgs[i].Value >>= aText;
                    break;
                }
            }

            if (aText == "English") this->langType = 0;
            else if (aText == "Russian") this->langType = 1;
            else if (aText == "Any") this->langType = 2;
        } else if (aURL.Path == "spinWordCount") {
            for (sal_Int32 i = 0; i < lArgs.getLength(); i++)
            {
                if (lArgs[i].Name == "Value")
                {
                    lArgs[i].Value >>= this->wordCount;
                    break;
                }
            }
        }


        return;



        if (aURL.Path == "ImageButtonCmd")
        {
            // open the LibreOffice web page
            ::rtl::OUString sURL("http://www.libreoffice.org");
            Reference<XSystemShellExecute> xSystemShellExecute(
                SystemShellExecute::create(mxContext));
            try
            {
                xSystemShellExecute->execute(sURL, ::rtl::OUString(), SystemShellExecuteFlags::URIS_ONLY);
            }
            catch (Exception &rEx)
            {
                (void)rEx;
            }
        }
        else if (aURL.Path == "ComboboxCmd")
        {
            // remove the text if it's in our list
            Sequence<NamedValue> aRemoveArgs(1);
            aRemoveArgs[0].Name = rtl::OUString("Text");
            aRemoveArgs[0].Value <<= maComboBoxText;
            SendCommand(aURL, ::rtl::OUString("RemoveEntryText"), aRemoveArgs, sal_True);

            // add the new text to the start of the list
            Sequence<NamedValue> aInsertArgs(2);
            aInsertArgs[0].Name = rtl::OUString("Pos");
            aInsertArgs[0].Value <<= sal_Int32(0);
            aInsertArgs[1].Name = rtl::OUString("Text");
            aInsertArgs[1].Value <<= maComboBoxText;
            SendCommand(aURL, ::rtl::OUString("InsertEntry"), aInsertArgs, sal_True);
        }
        else if (aURL.Path == "InsertEntry")
        {
            // Retrieve the text argument from the sequence property value
            rtl::OUString aText;
            for (sal_Int32 i = 0; i < lArgs.getLength(); i++)
            {
                if (lArgs[i].Name == "Text")
                {
                    lArgs[i].Value >>= aText;
                    break;
                }
            }

            // create new URL to address the combox box
            URL aCmdURL;
            aCmdURL.Path = "ComboboxCmd";
            aCmdURL.Protocol = "vnd.demo.complextoolbarcontrols.demoaddon:";
            aCmdURL.Complete = aCmdURL.Path + aCmdURL.Protocol;

            // set the selected item as text into the combobox
            Sequence<NamedValue> aArgs(1);
            aArgs[0].Name = "Text";
            aArgs[0].Value <<= aText;
            SendCommand(aCmdURL, ::rtl::OUString("SetText"), aArgs, sal_True);
        }
        else if (aURL.Path == "DropdownButtonCmd")
        {
            // Retrieve the text argument from the sequence property value
            rtl::OUString aText;
            for (sal_Int32 i = 0; i < lArgs.getLength(); i++)
            {
                if (lArgs[i].Name == "Text")
                {
                    lArgs[i].Value >>= aText;
                    break;
                }
            }

            // just enable this command

            // set enable flag according to selection
            if (aText == "Button Disabled")
                mbButtonEnabled = sal_False;
            else
                mbButtonEnabled = sal_True;

            // create new URL to address the image button
            URL aCmdURL;
            aCmdURL.Path = "Command1";
            aCmdURL.Protocol = "vnd.demo.complextoolbarcontrols.demoaddon:";
            aCmdURL.Complete = aCmdURL.Path + aCmdURL.Protocol;

            // create and initialize FeatureStateEvent with IsEnabled
            ::com::sun::star::frame::FeatureStateEvent aEvent;
            aEvent.FeatureURL = aCmdURL;
            aEvent.Source = (::com::sun::star::frame::XDispatch *)this;
            aEvent.IsEnabled = mbButtonEnabled;
            aEvent.Requery = sal_False;
            aEvent.State = Any();

            // Notify listener about new state
            Reference<XDispatch> xDispatch = aListenerHelper.GetDispatch(mxFrame, aURL.Path);
            aListenerHelper.Notify(mxFrame, aEvent.FeatureURL.Path, aEvent);
        }
        else if (aURL.Path == "SpinfieldCmd")
        {
        }
        else if (aURL.Path == "DropdownboxCmd")
        {
            // Retrieve the text argument from the sequence property value
            rtl::OUString aText;
            for (sal_Int32 i = 0; i < lArgs.getLength(); i++)
            {
                if (lArgs[i].Name == "Text")
                {
                    lArgs[i].Value >>= aText;
                    break;
                }
            }
        }
    }
}

void SAL_CALL 
BaseDispatch::addStatusListener(
    const Reference<XStatusListener> &xControl, 
    const URL &aURL
) {
    if (aURL.Protocol == "vnd.demo.complextoolbarcontrols.demoaddon:")
    {
        if (aURL.Path == "ImageButtonCmd")
        {
            // just enable this command
            ::com::sun::star::frame::FeatureStateEvent aEvent;
            aEvent.FeatureURL = aURL;
            aEvent.Source = (::com::sun::star::frame::XDispatch *)this;
            aEvent.IsEnabled = mbButtonEnabled;
            aEvent.Requery = sal_False;
            aEvent.State = Any();
            xControl->statusChanged(aEvent);
        }
        else if (aURL.Path == "ComboboxCmd")
        {
            // just enable this command
            ::com::sun::star::frame::FeatureStateEvent aEvent;
            aEvent.FeatureURL = aURL;
            aEvent.Source = (::com::sun::star::frame::XDispatch *)this;
            aEvent.IsEnabled = sal_True;
            aEvent.Requery = sal_False;
            aEvent.State = Any();
            xControl->statusChanged(aEvent);
        }
        else if (aURL.Path == "ToggleDropdownButtonCmd")
        {
            // A toggle dropdown box is normally used for a group of commands
            // where the user can select the last issued command easily.
            // E.g. a typical command group would be "Insert shape"
            Sequence<NamedValue> aArgs(1);

            // send command to set context menu content
            Sequence<rtl::OUString> aContextMenu(3);
            aContextMenu[0] = "Command 1";
            aContextMenu[1] = "Command 2";
            aContextMenu[2] = "Command 3";

            aArgs[0].Name = "List";
            aArgs[0].Value <<= aContextMenu;
            SendCommandTo(xControl, aURL, rtl::OUString("SetList"), aArgs, sal_True);

            // send command to check item on pos=0
            aArgs[0].Name = rtl::OUString("Pos");
            aArgs[0].Value <<= sal_Int32(0);
            SendCommandTo(xControl, aURL, ::rtl::OUString("CheckItemPos"), aArgs, sal_True);
        }
        else if (aURL.Path == "DropdownButtonCmd")
        {
            // A dropdown box is normally used for a group of dependent modes, where
            // the user can only select one. The modes cannot be combined.
            // E.g. a typical group would be left,right,center,block.
            Sequence<NamedValue> aArgs(1);

            // send command to set context menu content
            Sequence<rtl::OUString> aContextMenu(2);
            aContextMenu[0] = "Button Enabled";
            aContextMenu[1] = "Button Disabled";

            aArgs[0].Name = "List";
            aArgs[0].Value <<= aContextMenu;
            SendCommandTo(xControl, aURL, rtl::OUString("SetList"), aArgs, sal_True);

            // set position according to enable/disable state of button
            sal_Int32 nPos(mbButtonEnabled ? 0 : 1);

            // send command to check item on pos=0
            aArgs[0].Name = "Pos";
            aArgs[0].Value <<= nPos;
            SendCommandTo(xControl, aURL, ::rtl::OUString("CheckItemPos"), aArgs, sal_True);
        }
        else if (aURL.Path == "spinWordCount")
        {
            // A spin button
            Sequence<NamedValue> aArgs(3);

            // send command to initialize spin button
            aArgs[0].Name = "Value";
            aArgs[0].Value <<= int(1.0);
            aArgs[1].Name = "LowerLimit";
            aArgs[1].Value <<= int(1.0);
            aArgs[2].Name = "Step";
            aArgs[2].Value <<= int(1.0);

            SendCommandTo(xControl, aURL, rtl::OUString("SetValues"), aArgs, sal_True);
        }
        else if (aURL.Path == "setWordLanguage")
        {
            Sequence< rtl::OUString > aList( 3 );
            aList[0] = "English";
            aList[1] = "Russian";
            aList[2] = "Any";
            Sequence< NamedValue > aArgs( 1 );
            aArgs[0].Name = "List";
            aArgs[0].Value <<= aList;
            SendCommandTo( xControl, aURL, rtl::OUString("SetList"), aArgs, sal_True );

            // Set item 0
            aArgs[0].Name = rtl::OUString("Pos");
            aArgs[0].Value <<= sal_Int32(0);
            SendCommandTo( xControl, aURL, OUString("CheckItemPos"), aArgs, sal_True);
        }

        aListenerHelper.AddListener(mxFrame, xControl, aURL.Path);
    }
}

void SAL_CALL 
BaseDispatch::removeStatusListener(
    const Reference<XStatusListener> &xControl, 
    const URL &aURL
) {
    aListenerHelper.RemoveListener(mxFrame, xControl, aURL.Path);
}

void SAL_CALL 
BaseDispatch::controlEvent(
    const ControlEvent &Event
) {
    if (Event.aURL.Protocol == "vnd.demo.complextoolbarcontrols.demoaddon:")
    {
        if (Event.aURL.Path == "ComboboxCmd")
        {
            // We get notifications whenever the text inside the combobox has been changed.
            // We store the new text into a member.
            if (Event.Event == "TextChanged")
            {
                rtl::OUString aNewText;
                sal_Bool bHasText(sal_False);
                for (sal_Int32 i = 0; i < Event.aInformation.getLength(); i++)
                {
                    if (Event.aInformation[i].Name == "Text")
                    {
                        bHasText = Event.aInformation[i].Value >>= aNewText;
                        break;
                    }
                }

                if (bHasText)
                    maComboBoxText = aNewText;
            }
        }
    }
}

BaseDispatch::BaseDispatch(
    const Reference<XComponentContext> &rxContext,
    const Reference<XFrame> &xFrame,
    const ::rtl::OUString &rServiceName
) : mxContext(rxContext), 
    mxFrame(xFrame), 
    msDocService(rServiceName), 
    mbButtonEnabled(sal_True),
    maxWordLen(5),
    langType(0),
    wordCount(1) {
}

BaseDispatch::~BaseDispatch(
) {
    mxFrame.clear();
    mxContext.clear();
}
