
#ifndef INCLUDED_EXAMPLES_COMPLEXTOOLBARCONTROLS_MYJOB_H
#define INCLUDED_EXAMPLES_COMPLEXTOOLBARCONTROLS_MYJOB_H

#include <com/sun/star/task/XJob.hpp>
#include <com/sun/star/lang/IllegalArgumentException.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <cppuhelper/implbase2.hxx>

namespace com
{
    namespace sun
    {
        namespace star
        {
            namespace frame
            {
                class XModel;
                class XFrame;
            }
            namespace beans
            {
                struct NamedValue;
            }
        }
    }
}

class MyJob : public cppu::WeakImplHelper2<com::sun::star::task::XJob, com::sun::star::lang::XServiceInfo>
{
private:
    ::com::sun::star::uno::Reference<::com::sun::star::lang::XMultiServiceFactory> mxMSF;

public:
    MyJob(
        const ::com::sun::star::uno::Reference<::com::sun::star::lang::XMultiServiceFactory> &rxMSF
    ) : mxMSF(rxMSF) {}
    virtual ~MyJob() {}

    // XJob
    virtual ::com::sun::star::uno::Any SAL_CALL 
    execute(
        const ::com::sun::star::uno::Sequence<::com::sun::star::beans::NamedValue> &Arguments
    );

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL 
    getImplementationName();

    virtual sal_Bool SAL_CALL 
    supportsService(
        const ::rtl::OUString &ServiceName
    );

    virtual ::com::sun::star::uno::Sequence<::rtl::OUString> SAL_CALL 
    getSupportedServiceNames();
};


::rtl::OUString MyJob_getImplementationName();

sal_Bool SAL_CALL MyJob_supportsService(
    const ::rtl::OUString &ServiceName
);

::com::sun::star::uno::Sequence<::rtl::OUString> SAL_CALL 
MyJob_getSupportedServiceNames();

::com::sun::star::uno::Reference<::com::sun::star::uno::XInterface> SAL_CALL 
MyJob_createInstance(
    const ::com::sun::star::uno::Reference<::com::sun::star::lang::XMultiServiceFactory> &rSMgr
);

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
