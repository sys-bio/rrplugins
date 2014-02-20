#ifndef rre_jobs_apiH
#define rre_jobs_apiH
#include "rre_exporter.h"
#include "rre_types.h"
#include "rre_macros.h"
//---------------------------------------------------------------------------

#if defined(__cplusplus)
namespace rre
{
using namespace rrc;
extern "C"
{
#endif

/*!
 \brief Typedef for callback function, taking a void* parameter
 \ingroup multithreading
*/
typedef void (rre_cc *callBackFunc)(void*);

/*!
 \brief Run a roadrunner simulation in a thread
 \param[in] handle Handle to a RoadRunner instance
 \return Returns a handle to the Job if succesful, otherwise returns NULL
 \ingroup multiThreading
*/
RRE_DECLSPEC RRJobHandle rre_cc simulateJob(RRHandle handle);

/*!
 \brief Run a roadrunner simulation in a thread
 \param[in] handle Handle to a RoadRunner instance
 \param timeStart,timeEnd,numberOfPoints Parameters for the simulation
 \param fn1,fn2 Callback functions that are used internally in the thread.
 \param userData User supplied data that can be used in the supplied callback functions
 \return Returns a handle to the Job if succesful, otherwise returns NULL
 \ingroup multiThreading
*/
RRE_DECLSPEC RRJobHandle rre_cc simulateJobEx(RRHandle handle, double timeStart,
                                                        double timeEnd,    int numberOfPoints,
                                                        callBackFunc fn1, callBackFunc fn2, void* userData);

/*!
 \brief Run multiple simulations in a set of threads
 \param[in] handles Handle to a list of RoadRunner instances
 \param[in] nrOfThreads Number of threads to allocate in order to execute the jobs
 \return Returns a handle to a list of jobs if succesful, otherwise returns NULL
 \ingroup multiThreading
*/
RRE_DECLSPEC RRJobsHandle rre_cc simulateJobs(RRInstanceListPtr handles, int nrOfThreads);


/*!
 \brief Run multiple simulations in a set of threads
 \param[in] handles Handle to a list of RoadRunner instances
 \param[in] nrOfThreads Number of threads to allocate in order to execute the jobs
 \param timeStart,timeEnd,numberOfPoints Parameters for the simulation
 \param fn1,fn2 Callback functions that are used internally in the thread.
 \param userData User supplied data that can be used in the supplied callback functions
 \return Returns a handle to a list of jobs if succesful, otherwise returns NULL
 \ingroup multiThreading
*/RRE_DECLSPEC RRJobsHandle rre_cc simulateJobsEx(RRInstanceListPtr handles, int nrOfThreads,
                                                        double timeStart, double timeEnd, int numberOfPoints,
                                                        callBackFunc fn1, callBackFunc fn2, void* userData);

/*!
 \brief Load a model from a SBML file into a RoadRunner instances, using a Job
 \param[in] handle Handle to a RoadRunner instance
 \param[in] fileName file name (with optional full path) to a file that holds the SBML model
 \return Returns a handle to the Job if succesful, otherwise returns NULL
 \ingroup multiThreading
*/

RRE_DECLSPEC RRJobHandle rre_cc loadSBMLFromFileJob(RRHandle handle, const char* fileName);

/*!
 \brief Load a model from a SBML file into a RoadRunner instances, using a Job
 \param[in] handle Handle to a RoadRunner instance
 \param[in] fileName file name (or full path) to file that holds the SBML model
 \param[in] reCompile Boolean that forces recompilation if true. If false, no compilation occur if model dll exists
 \return Returns a handle to the Job if succesful, otherwise returns NULL
 \ingroup multiThreading
*/

RRE_DECLSPEC RRJobHandle rre_cc loadSBMLFromFileJobEx(RRHandle handle, const char* fileName, bool reCompile);

/*!
 \brief Load a model from a SBML file into a set of RoadRunner instances
 \param[in] handles Handle to a list of RoadRunner instances
 \param[in] fileName file name (or full path) to file that holds the SBML model
 \param[in] nrOfThreads Number of threads to allocate in order to execute the job
 \return Returns a handle to the Jobs if succesful, otherwise returns NULL
 \ingroup multiThreading
*/
RRE_DECLSPEC RRJobsHandle rre_cc loadSBMLFromFileJobs(RRInstanceListPtr handles, const char* fileName, int nrOfThreads);

/*!
 \brief Load a model from a SBML text string into a RoadRunner instances, using a Job
 \param[in] handle Handle to a RoadRunner instance
 \param[in] sbml String that holds the SBML model
 \return Returns a handle to the Job if succesful, otherwise returns NULL
 \ingroup multiThreading
*/
RRE_DECLSPEC RRJobHandle rre_cc loadSBMLJob(RRHandle handle, const char* sbml);

/*!
 \brief Load a model from a SBML text string into a RoadRunner instances, using a Job
 \param[in] handle Handle to a RoadRunner instance
 \param[in] sbml String that holds the SBML model
 \param[in] reCompile Boolean that forces recompilation if true. If false, no compilation occur if model dll exists
 \return Returns a handle to the Job if succesful, otherwise returns NULL
 \ingroup multiThreading
*/
RRE_DECLSPEC RRJobHandle rre_cc loadSBMLJobEx(RRHandle handle, const char* sbml, bool reCompile);

/*!
 \brief Load a model from a SBML tesxt string into a set of RoadRunner instances
 \param[in] handles Handle to a list of RoadRunner instances
 \param[in] sbml String that holds the SBML model
 \param[in] nrOfThreads Number of threads to allocate in order to execute the job
 \return Returns a handle to the Jobs if succesful, otherwise returns NULL
 \ingroup multiThreading
*/
RRE_DECLSPEC RRJobsHandle rre_cc loadSBMLJobs(RRInstanceListPtr handles, const char* sbml, int nrOfThreads);

/*!
 \brief Load a model from a SBML file into a set of RoadRunner instances
 \param[in] handles Handle to a list of RoadRunner instances
 \param[in] sbml string that holds the SBML model
 \param[in] nrOfThreads Number of threads to allocate in order to execute the job
 \param[in] force_recompile Indicates if a forced recompilation of the model should be executed
 \return Returns a handle to the Jobs if succesful, otherwise returns NULL
 \ingroup multiThreading
*/
RRE_DECLSPEC RRJobsHandle rre_cc loadSBMLJobsEx(RRInstanceListPtr handles, const char* sbml, int nrOfThreads, bool force_recompile);

/*!
 \brief Wait for jobs in thread to finish
 \param[in] handle Handle to a RoadRunner job
 \return Returns true if thread finsihed up properly, otherwise returns false
 \ingroup multiThreading
*/
RRE_DECLSPEC bool rre_cc waitForJob(RRJobHandle handle);

/*!
 \brief Wait for jobs in thread pool to finish
 \param[in] handle Handle to a list of RoadRunner jobs
 \return Returns true if threadpool finished up properly, otherwise returns false
 \ingroup multiThreading
*/
RRE_DECLSPEC bool rre_cc waitForJobs(RRJobsHandle handle);

/*!
 \brief Check if there are work being done on a job
 \param[in] handle Handle to a RoadRunner job
 \return Returns true if there are running threads, otherwise returns false
 \ingroup multiThreading
*/
RRE_DECLSPEC bool rre_cc isJobFinished(RRJobHandle handle);

/*!
 \brief Check if there are work being done on jobs
 \param[in] handle Handle to a list of RoadRunner jobs
 \return Returns true if there are running threads, otherwise returns false
 \ingroup multiThreading
*/
RRE_DECLSPEC bool rre_cc areJobsFinished(RRJobsHandle handle);

/*!
 \brief Get number of remaining jobs in a job list
 \param[in] handle Handle to a list of RoadRunner jobs
 \return Returns number of remaining, unfinished jobs. Returns -1 on failure
 \ingroup multiThreading
*/
RRE_DECLSPEC int rre_cc getNumberOfRemainingJobs(RRJobsHandle handle);


/*!
 \brief Free a job handle
 \param[in] handle Handle to a roadrunner job
 \return Returns true or false indicating if the function was succesful
 \ingroup multiThreading
*/
RRE_DECLSPEC bool rre_cc freeJob(RRJobHandle handle, RRJobType jt);

/*!
 \brief Free a jobs handle
 \param[in] handle Handle to a list of roadrunner jobs
 \return Returns true or false indicating if the function was succesful
 \ingroup multiThreading
*/

RRE_DECLSPEC bool rre_cc freeJobs(RRJobsHandle handle);

#if defined(__cplusplus)
}    //Extern "C"
}    //namespace
#endif

#endif
