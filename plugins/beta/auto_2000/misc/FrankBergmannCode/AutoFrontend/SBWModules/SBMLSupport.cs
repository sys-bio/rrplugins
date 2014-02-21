using System.Collections;
using System.Diagnostics;
using SBW;

namespace AutoFrontend.SBWModules
{
    public class SBMLSupport
    {
        /// <summary>
        ///     Tests reactions of the given SBML model, in case modifiers are referenced in kinetic laws, but not in the list of modifiers, the SBML will be modified. Returns the modified SBML string.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string addMissingModifiers(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string addMissingModifiers(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     This method checks the consistency of the currently loaded model, returning the number of consistency validations.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static int checkConsistency()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (int)
                    HighLevel.convertArray(oService.getMethod("int checkConsistency()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Converts a SBML level 1 document to level2 document.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string convertLevel1ToLevel2Impl(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string convertLevel1ToLevel2Impl(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Converts a SBML level 2 document to level1 document.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string convertLevel2ToLevel1Impl(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string convertLevel2ToLevel1Impl(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Converts a MathML string to mathematical infix expression.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string convertMathMLToString(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string convertMathMLToString(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Converts a power tag to ^. The input is a valid sbml string. The output is also an sbml string with power expressions converted.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string convertPowImpl(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string convertPowImpl(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Transforms the given SBML string as indicated by the Parameters. The parameters are the target level and target version of the SBML spec.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string convertSBML(string var0, int var1, int var2)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);
                oArguments.add(var1);
                oArguments.add(var2);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string convertSBML(string, int, int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Converts a mathematical infix expression to a MathML string.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string convertStringToMathML(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string convertStringToMathML(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     This method will modify all time-symbols in the model (first argument) to the time-identifier provided in the second argument (e.g. 'time').
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string convertTime(string var0, string var1)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);
                oArguments.add(var1);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string convertTime(string, string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     The returns 1 if the input string appears in the sbml document otherwise 0. The input string can be a species name/Id, parameter name/Id, compartment name/Id.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static bool exists(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (bool)
                    HighLevel.convertArray(oService.getMethod("boolean exists(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the annotation xml for the element with the given Id
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getAnnotation(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getAnnotation(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the description of the builtin funtion for the input string provided.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string[] getBuiltinFunctionInfo(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string[])
                    HighLevel.convertArray(
                        oService.getMethod("string[] getBuiltinFunctionInfo(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns a list of strings of all the builtin functions.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string[] getBuiltinFunctions()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string[])
                    HighLevel.convertArray(
                        oService.getMethod("string[] getBuiltinFunctions()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the name/Id of the compartment where the Species with the given speciesId is located
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getCompartmentIdBySpeciesId(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getCompartmentIdBySpeciesId(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns a derived unit definition for the model element with the given id. The return format will be a list of list of unit descriptions e.g.: { { \"mole\", exponent, multiplier, offset, scale},...}
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static ArrayList getDerivedUnitDefinition(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (ArrayList)
                    HighLevel.convertArray(
                        oService.getMethod("{} getDerivedUnitDefinition(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the Kineticlaw of reaction at the index value provided. The index can vary from 0 to (numOfReactions-1). If the index exceeds the total number of Reactions then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getKineticLaw(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(oService.getMethod("string getKineticLaw(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns a list of all the boundary species and their values together with and indicator whether this value is a concentration (true) or an amount (false). The return type will be a list of lists ex:- {{\"S1\",1.0,True},{\"S2\",2.0,False}}
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static ArrayList getListOfBoundarySpecies()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (ArrayList)
                    HighLevel.convertArray(
                        oService.getMethod("{} getListOfBoundarySpecies()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns a list of all the Boundary speciesIds.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static ArrayList getListOfBoundarySpeciesIds()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (ArrayList)
                    HighLevel.convertArray(
                        oService.getMethod("{} getListOfBoundarySpeciesIds()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     This returns all error messages of the ErrorLog as List of Lists with format: {string severity, int lineNumber, int columnNumber, int errorCode, string errorMessage}
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static ArrayList getListOfErrors()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (ArrayList)
                    HighLevel.convertArray(oService.getMethod("{} getListOfErrors()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns a list of all the floating species and their values together with and indicator whether this value is a concentration (true) or an amount (false). The return type will be a list of lists ex:- {{\"S1\",1.0,True},{\"S2\",2.0,False}}
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static ArrayList getListOfFloatingSpecies()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (ArrayList)
                    HighLevel.convertArray(
                        oService.getMethod("{} getListOfFloatingSpecies()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns a list of all the floating speciesIds.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static ArrayList getListOfFloatingSpeciesIds()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (ArrayList)
                    HighLevel.convertArray(
                        oService.getMethod("{} getListOfFloatingSpeciesIds()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns a list of both the global & local parameters and their values. The return type will be a list of lists ex:- {{\"K1\",1.0},{\"K2\",2.0}}
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static ArrayList getListOfParameters()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (ArrayList)
                    HighLevel.convertArray(oService.getMethod("{} getListOfParameters()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the modelId/Name given in sbml document
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getModelId()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(oService.getMethod("string getModelId()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the modelName/Id given in sbml document
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getModelName()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(oService.getMethod("string getModelName()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the notes xml for the element with the given Id
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNotes(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(oService.getMethod("string getNotes(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the name of the compartment where the floatingSpecies with the given index is located
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNthBoundarySpeciesCompartmentName(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getNthBoundarySpeciesCompartmentName(int)")
                                .call(oArguments)
                                .getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the id of the boundarySpecies for the input index. The index can vary from 0 to (numOfBoundarySpecies-1). If the index exceeds the total number of boundarySpecies then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNthBoundarySpeciesId(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getNthBoundarySpeciesId(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the name of the boundarySpecies for the input index. The index can vary from 0 to (numOfBoundarySpecies-1). If the index exceeds the total number of boundarySpecies then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNthBoundarySpeciesName(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getNthBoundarySpeciesName(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the Id of compartment for the input index. The index can vary from 0 to (numOfCompartments-1). If the index exceeds the total number of compartments then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNthCompartmentId(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getNthCompartmentId(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the name of compartment for the input index. The index can vary from 0 to (numOfCompartments-1). If the index exceeds the total number of compartments then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNthCompartmentName(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getNthCompartmentName(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     This returns the n'th (zero based and
        ///     < getNumErrors()) Error as List: { string severity, int lineNumber, int
        ///         columnNumber, int errorCode, string errorMessage}
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static ArrayList getNthError(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (ArrayList)
                    HighLevel.convertArray(oService.getMethod("{} getNthError(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the event at the index value provided. The return type is a list containing {trigger, delay, {lValue_eventAssignment1, rValue_eventAssignment1}, {lValue_eventAssignment2, rValue_eventAssignment2}, ...} The index can vary from 0 to (numOfEvents-1). If the index exceeds the total number of events then the method throws an exception.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static ArrayList getNthEvent(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (ArrayList)
                    HighLevel.convertArray(oService.getMethod("{} getNthEvent(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the name of the compartment where the floatingSpecies with the given index is located
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNthFloatingSpeciesCompartmentName(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getNthFloatingSpeciesCompartmentName(int)")
                                .call(oArguments)
                                .getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the id of the floatingSpecies for the input index. The index can vary from 0 to (numOfFloatingSpecies-1). If the index exceeds the total number of floatingSpecies then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNthFloatingSpeciesId(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getNthFloatingSpeciesId(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the name of the floatingSpecies for the input index. The index can vary from 0 to (numOfFloatingSpecies-1). If the index exceeds the total number of floatingSpecies then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNthFloatingSpeciesName(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getNthFloatingSpeciesName(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     The return type is a list containing {functionId, list of arguments, function body}. The index can vary from 0 to (numOfFunctionDefinitions-1). If the index exceeds the total number of function Definitions then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static ArrayList getNthFunctionDefinition(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (ArrayList)
                    HighLevel.convertArray(
                        oService.getMethod("{} getNthFunctionDefinition(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the id of the global parameter at index values provided. The index can vary from 0 to (numOfGlobalParameters-1). If the index exceeds the total number of Global Parameters then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNthGlobalParameterId(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getNthGlobalParameterId(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the name of the global parameter at index values provided. The index can vary from 0 to (numOfGlobalParameters-1). If the index exceeds the total number of Global Parameters then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNthGlobalParameterName(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getNthGlobalParameterName(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     The return type is a list containing {species id's} where the species modify the reaction. The index can vary from 0 to (numReactions-1). If the index exceeds the total number of reactions then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static ArrayList getNthListOfModifiers(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (ArrayList)
                    HighLevel.convertArray(
                        oService.getMethod("{} getNthListOfModifiers(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     The return type is a list containing lists of {species id's and stoichiometry} that are products of the reaction. The index can vary from 0 to (numReactions-1). If the index exceeds the total number of reactions then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static ArrayList getNthListOfProducts(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (ArrayList)
                    HighLevel.convertArray(
                        oService.getMethod("{} getNthListOfProducts(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     The return type is a list containing lists of {species id's and stoichiometry} that are reactants of the reaction. The index can vary from 0 to (numReactions-1). If the index exceeds the total number of reactions then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static ArrayList getNthListOfReactants(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (ArrayList)
                    HighLevel.convertArray(
                        oService.getMethod("{} getNthListOfReactants(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns 1 if a value is assigned to the parameter for the indicies values provided and 0 otherwise. The first input is the reaction index and it can vary from 0 to (numOfReactions-1). The second index varies from 0 to (numberOfParameters-1) of the input reaction index. If the first index exceeds the total number of Reactions or the second index exceeds the total number of Parameters of the	reaction then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static bool getNthParameterHasValue(int var0, int var1)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);
                oArguments.add(var1);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (bool)
                    HighLevel.convertArray(
                        oService.getMethod("boolean getNthParameterHasValue(int,int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the id of the parameter for the indicies values provided. The first input is the reaction index and it can vary from 0 to (numOfReactions-1). The second index varies from 0 to (localParameters-1) of the input reaction index. If the first index exceeds the total number of Reactions or the second index exceeds the total number of Parameters of the reaction then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNthParameterId(int var0, int var1)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);
                oArguments.add(var1);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getNthParameterId(int,int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the name of the parameter for the indicies values provided. The first input is the reaction index and it can vary from 0 to (numOfReactions-1). The second index varies from 0 to (localParameters-1) of the input reaction index. If the first index exceeds the total number of Reactions or the second index exceeds the total number of Parameters of the reaction then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNthParameterName(int var0, int var1)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);
                oArguments.add(var1);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getNthParameterName(int,int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the value of parameter for the indicies values provided. The first input is the reaction index and it can vary from 0 to (numOfReactions-1). The second index varies from 0 to (numberOfParameters-1) of the input reaction index. If the first index exceeds the total number of Reactions or the second index exceeds the total number of Parameters of the reaction then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static double getNthParameterValue(int var0, int var1)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);
                oArguments.add(var1);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (double)
                    HighLevel.convertArray(
                        oService.getMethod("double getNthParameterValue(int,int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the name of product for the indicies values provided. The first input is the reaction index and it can vary from 0 to (numOfReactions-1). The second index varies from 0 to (numberOfProducts-1) of the input reaction index. If the first index exceeds the total number of Reactions or the second index exceeds the total number of products of the reaction then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNthProductName(int var0, int var1)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);
                oArguments.add(var1);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getNthProductName(int,int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the name of stoichiometry value for the indicies values provided. The first input is the reaction index and it can vary from 0 to (numOfReactions-1). The second index varies from 0 to (numberOfProducts-1) of the input reaction index. If the first index exceeds the total number of Reactions or the second index exceeds the total number of products of the reaction then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static int getNthProductStoichiometry(int var0, int var1)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);
                oArguments.add(var1);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (int)
                    HighLevel.convertArray(
                        oService.getMethod("int getNthProductStoichiometry(int,int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the name of stoichiometry value for the indicies values provided. The first input is the reaction index and it can vary from 0 to (numOfReactions-1). The second index varies from 0 to (numberOfProducts-1) of the input reaction index. If the first index exceeds the total number of Reactions or the second index exceeds the total number of products of the reaction then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static double getNthProductStoichiometryDouble(int var0, int var1)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);
                oArguments.add(var1);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (double)
                    HighLevel.convertArray(
                        oService.getMethod("double getNthProductStoichiometryDouble(int,int)")
                                .call(oArguments)
                                .getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the name of reactant for the indicies values provided. The first input is the reaction index and it can vary from 0 to (numOfReactions-1). The second index varies from 0 to (numberOfReactants-1) of the input reaction index. If the first index exceeds the total number of Reactions or the second index exceeds the total number of reactants of the reaction then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNthReactantName(int var0, int var1)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);
                oArguments.add(var1);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getNthReactantName(int,int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the name of stoichiometry value for the indicies values provided. The first input is the reaction index and it can vary from 0 to (numOfReactions-1). The second index varies from 0 to (numberOfReactants-1) of the input reaction index. If the first index exceeds the total number of Reactions or the second index exceeds the total number of products of the reaction then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static int getNthReactantStoichiometry(int var0, int var1)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);
                oArguments.add(var1);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (int)
                    HighLevel.convertArray(
                        oService.getMethod("int getNthReactantStoichiometry(int,int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the name of stoichiometry value for the indicies values provided. The first input is the reaction index and it can vary from 0 to (numOfReactions-1). The second index varies from 0 to (numberOfReactants-1) of the input reaction index. If the first index exceeds the total number of Reactions or the second index exceeds the total number of products of the reaction then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static double getNthReactantStoichiometryDouble(int var0, int var1)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);
                oArguments.add(var1);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (double)
                    HighLevel.convertArray(
                        oService.getMethod("double getNthReactantStoichiometryDouble(int,int)")
                                .call(oArguments)
                                .getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the id of the reaction for the input index value. The index can vary from 0 to (numOfReactions-1). If the index exceeds the total number of Reactions then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNthReactionId(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getNthReactionId(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the name of the reaction for the input index value. The index can vary from 0 to (numOfReactions-1). If the index exceeds the total number of Reactions then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNthReactionName(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getNthReactionName(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the rule at the index value provided. The index can vary from 0 to (numOfRules-1). If the index exceeds the total number of rules then the method throws an exception.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNthRule(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(oService.getMethod("string getNthRule(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     The return string indicates the type of rule at the index provided. Eg., 'Assignment_Rule', 'Algebraic_Rule', 'Rate_Rule', 'Parameter_Rule'; 'Species_Concentration_Rule'; 'Compartment_Volume_Rule'. The index can vary from 0 to (numOfRules-1). If the index exceeds the total number of rules then the method throws an exception.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getNthRuleType(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(oService.getMethod("string getNthRuleType(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the number of boundary species in the sbml document
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static int getNumBoundarySpecies()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (int)
                    HighLevel.convertArray(
                        oService.getMethod("int getNumBoundarySpecies()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the number of compartments listed in the sbml document
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static int getNumCompartments()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (int)
                    HighLevel.convertArray(oService.getMethod("int getNumCompartments()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     This method returns the number of Warnings/Errors listed in the ErrorLog.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static int getNumErrors()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (int) HighLevel.convertArray(oService.getMethod("int getNumErrors()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the total number of Event in the sbml.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static int getNumEvents()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (int) HighLevel.convertArray(oService.getMethod("int getNumEvents()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the number of floating species in the sbml document
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static int getNumFloatingSpecies()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (int)
                    HighLevel.convertArray(
                        oService.getMethod("int getNumFloatingSpecies()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the number offunction Definitions listed in the sbml document
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static int getNumFunctionDefinitions()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (int)
                    HighLevel.convertArray(
                        oService.getMethod("int getNumFunctionDefinitions()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the number of global parameters in the sbml document
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static int getNumGlobalParameters()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (int)
                    HighLevel.convertArray(
                        oService.getMethod("int getNumGlobalParameters()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the total number of local parameters for the input reaction index.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static int getNumParameters(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (int)
                    HighLevel.convertArray(oService.getMethod("int getNumParameters(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the number of products for tbe reaction index. The index can vary from 0 to (numOfReactions-1). If the index exceeds the total number of Reactions then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static int getNumProducts(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (int)
                    HighLevel.convertArray(oService.getMethod("int getNumProducts(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the number of reactants for tbe reaction index. The index can vary from 0 to (numOfReactions-1). If the index exceeds the total number of Reactions then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static int getNumReactants(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (int)
                    HighLevel.convertArray(oService.getMethod("int getNumReactants(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the number of reactions listed in the sbml document
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static int getNumReactions()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (int)
                    HighLevel.convertArray(oService.getMethod("int getNumReactions()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the total number of Rules in the sbml.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static int getNumRules()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (int) HighLevel.convertArray(oService.getMethod("int getNumRules()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the outside compartment for the input. The input should be a compartment name for level 1 and compartment id for level 2. Throws an exception if the id or name is not found.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getOutsideCompartment(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getOutsideCompartment(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Modifies the names of local parameters by adding reaction name at the beginning and promotes them to global.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getParamPromotedSBML(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string getParamPromotedSBML(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the currently loaded sbml document
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string getSBML()
        {
            try
            {
                var oArguments = new DataBlockWriter();

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string) HighLevel.convertArray(oService.getMethod("string getSBML()").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the SBO Term for the element with the given Id
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static int getSBOTerm(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (int)
                    HighLevel.convertArray(oService.getMethod("int getSBOTerm(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Gets the value assigned to the input string. The input string can be a species name/Id, parameter name/Id, compartment name/Id.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static double getValue(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (double)
                    HighLevel.convertArray(oService.getMethod("double getValue(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns True if the given species name/Id has an initial amount set, False otherwise.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static bool hasInitialAmount(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (bool)
                    HighLevel.convertArray(
                        oService.getMethod("boolean hasInitialAmount(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns True if the given species name/Id has an initial concentration set, False otherwise.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static bool hasInitialConcentration(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (bool)
                    HighLevel.convertArray(
                        oService.getMethod("boolean hasInitialConcentration(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Tests whether the element with the given Id has an SBO Term set, returns 'true' if it has, 'false' otherwise.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static bool hasSBOTerm(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (bool)
                    HighLevel.convertArray(oService.getMethod("boolean hasSBOTerm(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns the 1 if the input string has a value and 0 otherwise. The input string can be a species name/Id, parameter name/Id, compartment name/Id.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static bool hasValue(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (bool)
                    HighLevel.convertArray(oService.getMethod("boolean hasValue(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     This method checks whether the given species id is marked as constant.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static bool isConstantImpl(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (bool)
                    HighLevel.convertArray(
                        oService.getMethod("boolean isConstantImpl(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Returns 1 if the reaction for the input index value is reversible and 0 otherwise. The index can vary from 0 to (numOfReactions-1). If the index exceeds the total number of Reactions then the method throws an exception
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static bool isReactionReversible(int var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (bool)
                    HighLevel.convertArray(
                        oService.getMethod("boolean isReactionReversible(int)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Loads the sbml document. The input string must be a valid sbml document. An exception will be thrown if there are fatal errors in the input string.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static void loadSBML(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                oService.getMethod("void loadSBML(string)").call(oArguments);
                return;
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Sets the Annotation for the element with the given id, to the xml provided. (argument: id, xml-sbml-annotation)
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static void setAnnotation(string var0, string var1)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);
                oArguments.add(var1);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                oService.getMethod("void setAnnotation(string, string)").call(oArguments);
                return;
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Sets the modelId/Name of the currently loaded model.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static void setModelId(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                oService.getMethod("void setModelId(string)").call(oArguments);
                return;
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Sets the notes for the element with the given id, to the xml provided. (argument: id, xml-sbml-annotation)
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static void setNotes(string var0, string var1)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);
                oArguments.add(var1);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                oService.getMethod("void setNotes(string, string)").call(oArguments);
                return;
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Sets the SBO Term of the given element.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static void setSBOTerm(string var0, int var1)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);
                oArguments.add(var1);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                oService.getMethod("void setSBOTerm(string,int)").call(oArguments);
                return;
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Sets the value of the species name/Id, parameter name/Id, compartment name/Id to the given value.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static void setValue(string var0, double var1)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);
                oArguments.add(var1);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                oService.getMethod("void setValue(string,double)").call(oArguments);
                return;
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Validates the input sbml document. The input string must be a valid sbml document. An exception will be thrown if there are fatal errors in the input string.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string validateSBML(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string validateSBML(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }

        /// <summary>
        ///     Validates the current model and performs consistency checks.
        /// </summary>
        [DebuggerStepThrough, DebuggerHidden]
        public static string validateWithConsistency(string var0)
        {
            try
            {
                var oArguments = new DataBlockWriter();
                oArguments.add(var0);

                LowLevel.SBWConnect();
                var oModule = new Module("edu.caltech.NOMClipboard");
                Service oService = oModule.getService("NOM");
                return
                    (string)
                    HighLevel.convertArray(
                        oService.getMethod("string validateWithConsistency(string)").call(oArguments).getObject());
            }
            catch (SBWException e)
            {
                throw e;
            }
        }
    }
}