
#include <cppuhelper/factory.hxx>
#include <uno/lbnames.h>

#include "MyProtocolHandler.h"
#include "MyListener.h"

extern "C"
{
    SAL_DLLPUBLIC_EXPORT void *SAL_CALL 
    component_getFactory(
        const char *pImplName,
        void *pServiceManager,
        void *pRegistryKey
    ) {
        if (!pServiceManager || !pImplName)
            return 0;

        css::uno::Reference<css::uno::XInterface> xFactory;
        css::uno::Reference<css::lang::XMultiServiceFactory> xSMGR(
            reinterpret_cast<css::lang::XMultiServiceFactory *>(pServiceManager),
            css::uno::UNO_QUERY
        );
        ::rtl::OUString sImplName = ::rtl::OUString::createFromAscii(pImplName);

        if (sImplName == MYLISTENER_IMPLEMENTATIONNAME)
        {
            css::uno::Sequence<::rtl::OUString> lNames(1);
            lNames[0] = MYLISTENER_IMPLEMENTATIONNAME;
            xFactory = ::cppu::createSingleFactory(xSMGR, sImplName, MyListener::st_createInstance, lNames);
        }
        else if (sImplName == MYPROTOCOLHANDLER_IMPLEMENTATIONNAME)
        {
            css::uno::Sequence<::rtl::OUString> lNames(1);
            lNames[0] = MYPROTOCOLHANDLER_SERVICENAME;
            xFactory = ::cppu::createSingleComponentFactory(MyProtocolHandler_createInstance, sImplName, lNames);
        }

        if (!xFactory.is())
            return 0;

        xFactory->acquire();
        return xFactory.get();
    }

    SAL_DLLPUBLIC_EXPORT void SAL_CALL 
    component_getImplementationEnvironment(
        char const **ppEnvTypeName, 
        uno_Environment **
    ) {
        *ppEnvTypeName = CPPU_CURRENT_LANGUAGE_BINDING_NAME;
    }

} // extern C
