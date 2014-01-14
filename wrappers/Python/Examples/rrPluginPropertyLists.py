from rrplugins import *

listParaHandle = createProperty("myList", "listOfProperties", "a Hint")

#Should be empty
print getNamesFromPropertyList(listParaHandle)

#Add a new parameter
aParameterHandle = createProperty("newOne", "double", "the hint")
addPropertyToList(listParaHandle, aParameterHandle)

setDoubleProperty(aParameterHandle, 34)
print getDoubleProperty(aParameterHandle)

#Or you can use
print getProperty(aParameterHandle)

#Should not be empty
print getNamesFromPropertyList (listParaHandle)

#Get the parameter
paraHandle = getFirstProperty(listParaHandle)

print getPropertyHint (paraHandle)
print getPropertyInfo (paraHandle)
print getNamesFromPropertyList (listParaHandle)


print clearPropertyList(listParaHandle)
#Should be empty
print getNamesFromPropertyList (listParaHandle)

freeProperty(listParaHandle)

