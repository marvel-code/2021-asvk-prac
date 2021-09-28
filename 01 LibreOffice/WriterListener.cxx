
#include "MyListener.h"

#include <com/sun/star/lang/XMultiServiceFactory.hpp>

void SAL_CALL 
WriterListener::notifyEvent(
    const ::com::sun::star::document::EventObject &aEvent
) {
}

void SAL_CALL 
WriterListener::disposing(
    const com::sun::star::lang::EventObject &aSource
) {
}

WriterListener::WriterListener(
    const ::com::sun::star::uno::Reference<::com::sun::star::lang::XMultiServiceFactory> &rxMSF
) : mxMSF(rxMSF) {
}
