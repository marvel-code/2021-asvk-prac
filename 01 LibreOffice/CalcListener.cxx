
#include "MyListener.h"
#include <com/sun/star/lang/XMultiServiceFactory.hpp>

void SAL_CALL 
CalcListener::notifyEvent(
    const ::com::sun::star::document::EventObject &aEvent
) {}

void SAL_CALL 
CalcListener::disposing(
    const com::sun::star::lang::EventObject &aSource
) {}
