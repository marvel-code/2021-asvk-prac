
#ifndef INCLUDED_EXAMPLES_COMPLEXTOOLBARCONTROLS_MYLISTENER_H
#define INCLUDED_EXAMPLES_COMPLEXTOOLBARCONTROLS_MYLISTENER_H

#include <sal/config.h>

#include <com/sun/star/lang/IllegalArgumentException.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/task/XJob.hpp>
#include <com/sun/star/document/XEventListener.hpp>
#include <cppuhelper/implbase1.hxx>
#include <cppuhelper/implbase2.hxx>

#define MYLISTENER_IMPLEMENTATIONNAME "vnd.My.impl.NewDocListener"
#define MYLISTENER_SERVICENAME "vnd.My.NewDocListener"

/**
 * Register in the Office configuration as job.
 * This is called automatically for all new opened documents. You receive
 * a reference of the opened document and then you can check if it's a
 * supported format. (We are only interested in Writer documents.)
 *
 * @see WriterListener
 */
class MyListener : public cppu::WeakImplHelper2<css::task::XJob, css::lang::XServiceInfo>
{
private:
    css::uno::Reference<css::lang::XMultiServiceFactory> m_xSMGR;

public:
    MyListener(
        const css::uno::Reference<css::lang::XMultiServiceFactory> &xSMGR
    );
    virtual ~MyListener(
    );

    // XJob
    virtual css::uno::Any SAL_CALL 
    execute(
        const css::uno::Sequence<css::beans::NamedValue> &lArguments
    );

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL 
    getImplementationName(
    );

    virtual sal_Bool SAL_CALL 
    supportsService(
        const ::rtl::OUString &sServiceName
    );

    virtual css::uno::Sequence<::rtl::OUString> SAL_CALL 
    getSupportedServiceNames(
    );

public:
    static css::uno::Reference<css::uno::XInterface> 
    st_createInstance(
        const css::uno::Reference<css::lang::XMultiServiceFactory> &xSMGR
    );
};

class CalcListener : public cppu::WeakImplHelper1<css::document::XEventListener>
{
private:
    ::com::sun::star::uno::Reference<::com::sun::star::lang::XMultiServiceFactory> mxMSF;

public:
    CalcListener(const css::uno::Reference<css::lang::XMultiServiceFactory> &rxMSF)
        : mxMSF(rxMSF)
    {
    }

    virtual ~CalcListener()
    {
    }

    // document.XEventListener
    virtual void SAL_CALL notifyEvent(const css::document::EventObject &aEvent);
    virtual void SAL_CALL disposing(const css::lang::EventObject &aEvent);
};

class WriterListener : public cppu::WeakImplHelper1<css::document::XEventListener>
{
private:
    css::uno::Reference<css::lang::XMultiServiceFactory> mxMSF;

public:
    WriterListener(
        const css::uno::Reference<css::lang::XMultiServiceFactory> &rxMSF
    );

    virtual 
    ~WriterListener(
    ) {}

    // document.XEventListener
    virtual void SAL_CALL 
    notifyEvent(
        const css::document::EventObject &aEvent
    );

    virtual void SAL_CALL 
    disposing(
        const css::lang::EventObject &aEvent
    );
};

#endif
