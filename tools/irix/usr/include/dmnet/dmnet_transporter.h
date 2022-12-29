/*
 * dmnet_plugin_transporter.h -- 
 *      parameters for fibre channel/transporter connexions
 *
 */

#ifndef _DMNET_PLUGIN_TRANSPORTER_HEADER
#define _DMNET_PLUGIN_TRANSPORTER_HEADER

#ifdef _cplusplus
extern "C" {
#endif  
  
  /*
   * definitions for DMparams list
   * "values" below refers to values stored in the DMparams list
   */


  /* A string parameter may be set before dmNetConnect()/dmNetListen()
   * is called.  It should specify the desired local hostname as
   * relevant to the fibre channel network, if the content receiver 
   * wishes to specify a fibre channel interface locally.  Consult the 
   * file /etc/NLPorts for information about appropriate names.
   *
   * If DMNET_TRANSPORTER_LOCAL_HOSTNAME is set in the DMparams list
   * of the DMnetconnection cnp, the content receiver plugin will limit
   * connections to the named interface.  
   * (Receiver-side use only).
   */
#define DMNET_TRANSPORTER_LOCAL_HOSTNAME "DMNET_TRANSPORTER_LOCAL_HOSTNAME"
    

  /*
   * A string parameter may be set before dmNetAccept if 
   * DMNET_REMOTE_HOSTNAME is not a valid fibre channel hostname. 
   * (Sender-side use only)
   */
#define DMNET_TRANSPORTER_REMOTE_HOSTNAME "DMNET_TRANSPORTER_REMOTE_HOSTNAME"


  
#ifdef _cplusplus
}
#endif
#endif
