#pragma once
#include <stdbool.h>

#include "esp_bt_defs.h"
#include "esp_err.h"
#ifdef __cplusplus
extern "C" {
#endif

/// Advertising data maximum length
#define ESP_BLE_ADV_DATA_LEN_MAX 31
/// Scan response data maximum length
#define ESP_BLE_SCAN_RSP_DATA_LEN_MAX 31

#define ESP_BLE_ADV_FLAG_LIMIT_DISC (0x01 << 0)
#define ESP_BLE_ADV_FLAG_GEN_DISC (0x01 << 1)
#define ESP_BLE_ADV_FLAG_BREDR_NOT_SPT (0x01 << 2)
#define ESP_BLE_ADV_FLAG_DMT_CONTROLLER_SPT (0x01 << 3)
#define ESP_BLE_ADV_FLAG_DMT_HOST_SPT (0x01 << 4)
#define ESP_BLE_ADV_FLAG_NON_LIMIT_DISC (0x00)

#define ESP_LE_AUTH_BOND 0x01 /*!< 1 << 0 */ /* relate to BTM_LE_AUTH_BOND in stack/btm_api.h */

#define ESP_IO_CAP_NONE 3 /*!< NoInputNoOutput */ /* relate to BTM_IO_CAP_NONE in stack/btm_api.h */

typedef enum {
  ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT = 0,      /*!< When advertising data set complete, the event comes */
  ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT,     /*!< When scan response data set complete, the event comes */
  ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT,        /*!< When scan parameters set complete, the event comes */
  ESP_GAP_BLE_SCAN_RESULT_EVT,                    /*!< When one scan result ready, the event comes each time */
  ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT,      /*!< When raw advertising data set complete, the event comes */
  ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT, /*!< When raw advertising data set complete, the event comes */
  ESP_GAP_BLE_ADV_START_COMPLETE_EVT,             /*!< When starting advertising complete, the event comes */
  ESP_GAP_BLE_SCAN_START_COMPLETE_EVT,            /*!< When starting scan complete, the event comes */
  ESP_GAP_BLE_AUTH_CMPL_EVT,                      /*!< Authentication complete indication. */
  ESP_GAP_BLE_KEY_EVT,                            /*!< BLE  key event for peer device keys */
  ESP_GAP_BLE_SEC_REQ_EVT,                        /*!< BLE  security request */
  ESP_GAP_BLE_PASSKEY_NOTIF_EVT,                  /*!< passkey notification event */
  ESP_GAP_BLE_PASSKEY_REQ_EVT,                    /*!< passkey request event */
  ESP_GAP_BLE_OOB_REQ_EVT,                        /*!< OOB request event */
  ESP_GAP_BLE_LOCAL_IR_EVT,                       /*!< BLE local IR event */
  ESP_GAP_BLE_LOCAL_ER_EVT,                       /*!< BLE local ER event */
  ESP_GAP_BLE_NC_REQ_EVT,                         /*!< Numeric Comparison request event */
  ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT,              /*!< When stopping adv complete, the event comes */
  ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT,             /*!< When stopping scan complete, the event comes */
  ESP_GAP_BLE_SET_STATIC_RAND_ADDR_EVT,           /*!< When setting the static rand address complete, the event comes */
  ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT,             /*!< When updating connection parameters complete, the event comes */
  ESP_GAP_BLE_SET_PKT_LENGTH_COMPLETE_EVT,        /*!< When setting pkt length complete, the event comes */
  ESP_GAP_BLE_SET_LOCAL_PRIVACY_COMPLETE_EVT,     /*!< When enabling/disabling privacy on the local device complete, the
                                                     event comes */
  ESP_GAP_BLE_REMOVE_BOND_DEV_COMPLETE_EVT,       /*!< When removing the bond device complete, the event comes */
  ESP_GAP_BLE_CLEAR_BOND_DEV_COMPLETE_EVT,        /*!< When clearing the bond device clear complete, the event comes */
  ESP_GAP_BLE_GET_BOND_DEV_COMPLETE_EVT,          /*!< When getting the bond device list complete, the event comes */
  ESP_GAP_BLE_READ_RSSI_COMPLETE_EVT,             /*!< When reading the rssi complete, the event comes */
  ESP_GAP_BLE_UPDATE_WHITELIST_COMPLETE_EVT,      /*!< When adding or removing whitelist complete, the event comes */
  ESP_GAP_BLE_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_COMPLETE_EVT, /*!< When updating duplicate exceptional list complete,
                                                                 the event comes */
  ESP_GAP_BLE_SET_CHANNELS_EVT, /*!< When setting BLE channels complete, the event comes */
  ESP_GAP_BLE_EVT_MAX,
} esp_gap_ble_cb_event_t;

/// Sub Event of ESP_GAP_BLE_SCAN_RESULT_EVT
typedef enum {
  ESP_GAP_SEARCH_INQ_RES_EVT = 0,            /*!< Inquiry result for a peer device. */
  ESP_GAP_SEARCH_INQ_CMPL_EVT = 1,           /*!< Inquiry complete. */
  ESP_GAP_SEARCH_DISC_RES_EVT = 2,           /*!< Discovery result for a peer device. */
  ESP_GAP_SEARCH_DISC_BLE_RES_EVT = 3,       /*!< Discovery result for BLE GATT based service on a peer device. */
  ESP_GAP_SEARCH_DISC_CMPL_EVT = 4,          /*!< Discovery complete. */
  ESP_GAP_SEARCH_DI_DISC_CMPL_EVT = 5,       /*!< Discovery complete. */
  ESP_GAP_SEARCH_SEARCH_CANCEL_CMPL_EVT = 6, /*!< Search cancelled */
  ESP_GAP_SEARCH_INQ_DISCARD_NUM_EVT = 7,    /*!< The number of pkt discarded by flow control */
} esp_gap_search_evt_t;
typedef struct esp_ble_pkt_data_length_params_t {
} esp_ble_pkt_data_length_params_t;
typedef struct esp_ble_wl_opration_t {
} esp_ble_wl_opration_t;
typedef struct esp_duplicate_info_t {
} esp_duplicate_info_t;

#define ESP_BT_OCTET16_LEN 16
typedef uint8_t esp_bt_octet16_t[ESP_BT_OCTET16_LEN]; /* octet array: size 16 */

#define ESP_BT_OCTET8_LEN 8
typedef uint8_t esp_bt_octet8_t[ESP_BT_OCTET8_LEN]; /* octet array: size 8 */

typedef struct {
  esp_bt_octet16_t ltk; /*!< The long term key*/
  esp_bt_octet8_t rand; /*!< The random number*/
  uint16_t ediv;        /*!< The ediv value*/
  uint8_t sec_level;    /*!< The security level of the security link*/
  uint8_t key_size;     /*!< The key size(7~16) of the security link*/
} esp_ble_penc_keys_t;  /*!< The key type*/

/**
 * @brief  BLE CSRK keys
 */
typedef struct {
  uint32_t counter;      /*!< The counter */
  esp_bt_octet16_t csrk; /*!< The csrk key */
  uint8_t sec_level;     /*!< The security level */
} esp_ble_pcsrk_keys_t;  /*!< The pcsrk key type */

typedef struct {
  esp_bt_octet16_t irk;          /*!< The irk value */
  esp_ble_addr_type_t addr_type; /*!< The address type */
  esp_bd_addr_t static_addr;     /*!< The static address */
} esp_ble_pid_keys_t;            /*!< The pid key type */

typedef struct {
  esp_ble_key_mask_t key_mask;    /*!< the key mask to indicate witch key is present */
  esp_ble_penc_keys_t penc_key;   /*!< received peer encryption key */
  esp_ble_pcsrk_keys_t pcsrk_key; /*!< received peer device SRK */
  esp_ble_pid_keys_t pid_key;     /*!< peer device ID key */
} esp_ble_bond_key_info_t;        /*!< ble bond key information value type */

typedef struct {
  esp_bd_addr_t bd_addr;            /*!< peer address */
  esp_ble_bond_key_info_t bond_key; /*!< the bond key information */
} esp_ble_bond_dev_t;               /*!< the ble bond device type */

typedef enum {
  ESP_BLE_EVT_CONN_ADV = 0x00,     /*!< Connectable undirected advertising (ADV_IND) */
  ESP_BLE_EVT_CONN_DIR_ADV = 0x01, /*!< Connectable directed advertising (ADV_DIRECT_IND) */
  ESP_BLE_EVT_DISC_ADV = 0x02,     /*!< Scannable undirected advertising (ADV_SCAN_IND) */
  ESP_BLE_EVT_NON_CONN_ADV = 0x03, /*!< Non connectable undirected advertising (ADV_NONCONN_IND) */
  ESP_BLE_EVT_SCAN_RSP = 0x04,     /*!< Scan Response (SCAN_RSP) */
} esp_ble_evt_type_t;

typedef struct {
  bool set_scan_rsp;    /*!< Set this advertising data as scan response or not*/
  bool include_name;    /*!< Advertising data include device name or not */
  bool include_txpower; /*!< Advertising data include TX power */
  int min_interval;     /*!< Advertising data show slave preferred connection min interval.
                          The connection interval in the following manner:
                          connIntervalmin = Conn_Interval_Min * 1.25 ms
                          Conn_Interval_Min range: 0x0006 to 0x0C80
                          Value of 0xFFFF indicates no specific minimum.
                          Values not defined above are reserved for future use.*/

  int max_interval; /*!< Advertising data show slave preferred connection max interval.
                      The connection interval in the following manner:
                      connIntervalmax = Conn_Interval_Max * 1.25 ms
                      Conn_Interval_Max range: 0x0006 to 0x0C80
                      Conn_Interval_Max shall be equal to or greater than the Conn_Interval_Min.
                      Value of 0xFFFF indicates no specific maximum.
                      Values not defined above are reserved for future use.*/

  int appearance;               /*!< External appearance of device */
  uint16_t manufacturer_len;    /*!< Manufacturer data length */
  uint8_t *p_manufacturer_data; /*!< Manufacturer data point */
  uint16_t service_data_len;    /*!< Service data length */
  uint8_t *p_service_data;      /*!< Service data point */
  uint16_t service_uuid_len;    /*!< Service uuid length */
  uint8_t *p_service_uuid;      /*!< Service uuid array point */
  uint8_t flag;                 /*!< Advertising flag of discovery mode, see BLE_ADV_DATA_FLAG detail */
} esp_ble_adv_data_t;

/// Advertising mode
typedef enum {
  ADV_TYPE_IND = 0x00,
  ADV_TYPE_DIRECT_IND_HIGH = 0x01,
  ADV_TYPE_SCAN_IND = 0x02,
  ADV_TYPE_NONCONN_IND = 0x03,
  ADV_TYPE_DIRECT_IND_LOW = 0x04,
} esp_ble_adv_type_t;

/// Advertising channel mask
typedef enum {
  ADV_CHNL_37 = 0x01,
  ADV_CHNL_38 = 0x02,
  ADV_CHNL_39 = 0x04,
  ADV_CHNL_ALL = 0x07,
} esp_ble_adv_channel_t;
typedef enum {
  /// Allow both scan and connection requests from anyone
  ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY = 0x00,
  /// Allow both scan req from White List devices only and connection req from anyone
  ADV_FILTER_ALLOW_SCAN_WLST_CON_ANY,
  /// Allow both scan req from anyone and connection req from White List devices only
  ADV_FILTER_ALLOW_SCAN_ANY_CON_WLST,
  /// Allow scan and connection requests from White List devices only
  ADV_FILTER_ALLOW_SCAN_WLST_CON_WLST,
  /// Enumeration end value for advertising filter policy value check
} esp_ble_adv_filter_t;

/// Advertising parameters

typedef struct {
  uint16_t adv_int_min;               /*!< Minimum advertising interval for
                                          undirected and low duty cycle directed advertising.
                                          Range: 0x0020 to 0x4000 Default: N = 0x0800 (1.28 second)
                                          Time = N * 0.625 msec Time Range: 20 ms to 10.24 sec */
  uint16_t adv_int_max;               /*!< Maximum advertising interval for
                                          undirected and low duty cycle directed advertising.
                                          Range: 0x0020 to 0x4000 Default: N = 0x0800 (1.28 second)
                                          Time = N * 0.625 msec Time Range: 20 ms to 10.24 sec Advertising max interval */
  esp_ble_adv_type_t adv_type;        /*!< Advertising type */
  esp_ble_addr_type_t own_addr_type;  /*!< Owner bluetooth device address type */
  esp_bd_addr_t peer_addr;            /*!< Peer device bluetooth device address */
  esp_ble_addr_type_t peer_addr_type; /*!< Peer device bluetooth device address type, only support public address type
                                         and random address type */
  esp_ble_adv_channel_t channel_map;  /*!< Advertising channel map */
  esp_ble_adv_filter_t adv_filter_policy; /*!< Advertising filter policy */
} esp_ble_adv_params_t;

typedef enum {
  ESP_BLE_SM_PASSKEY = 0,
  /* Authentication requirements of local device */
  ESP_BLE_SM_AUTHEN_REQ_MODE,
  /* The IO capability of local device */
  ESP_BLE_SM_IOCAP_MODE,
  /* Initiator Key Distribution/Generation */
  ESP_BLE_SM_SET_INIT_KEY,
  /* Responder Key Distribution/Generation */
  ESP_BLE_SM_SET_RSP_KEY,
  /* Maximum Encryption key size to support */
  ESP_BLE_SM_MAX_KEY_SIZE,
  /* Minimum Encryption key size requirement from Peer */
  ESP_BLE_SM_MIN_KEY_SIZE,
  /* Set static Passkey */
  ESP_BLE_SM_SET_STATIC_PASSKEY,
  /* Reset static Passkey */
  ESP_BLE_SM_CLEAR_STATIC_PASSKEY,
  /* Accept only specified SMP Authentication requirement */
  ESP_BLE_SM_ONLY_ACCEPT_SPECIFIED_SEC_AUTH,
  /* Enable/Disable OOB support */
  ESP_BLE_SM_OOB_SUPPORT,
  /* Appl encryption key size */
  ESP_BLE_APP_ENC_KEY_SIZE,
  ESP_BLE_SM_MAX_PARAM,
} esp_ble_sm_param_t;

typedef struct {
  esp_bd_addr_t bd_addr;   /*!< peer address */
  uint32_t passkey;        /*!< the numeric value for comparison. If just_works, do not show this number to UI */
} esp_ble_sec_key_notif_t; /*!< BLE key notify type*/

typedef struct {
  esp_bd_addr_t bd_addr; /*!< peer address */
} esp_ble_sec_req_t;     /*!< BLE security request type*/

typedef uint8_t esp_ble_key_type_t;
typedef uint8_t esp_ble_io_cap_t;
typedef struct {
  esp_bt_octet16_t ltk; /*!< The long term key */
  uint16_t div;         /*!< The div value */
  uint8_t key_size;     /*!< The key size of the security link */
  uint8_t sec_level;    /*!< The security level of the security link */
} esp_ble_lenc_keys_t;
typedef struct {
  uint32_t counter;      /*!< The counter value */
  uint16_t div;          /*!< The div value */
  uint8_t sec_level;     /*!< The security level of the security link */
  esp_bt_octet16_t csrk; /*!< The csrk key value */
} esp_ble_lcsrk_keys;
typedef union {
  esp_ble_penc_keys_t penc_key;   /*!< received peer encryption key */
  esp_ble_pcsrk_keys_t pcsrk_key; /*!< received peer device SRK */
  esp_ble_pid_keys_t pid_key;     /*!< peer device ID key */
  esp_ble_lenc_keys_t lenc_key;   /*!< local encryption reproduction keys LTK = = d1(ER,DIV,0)*/
  esp_ble_lcsrk_keys lcsrk_key;   /*!< local device CSRK = d1(ER,DIV,1)*/
} esp_ble_key_value_t;            /*!< ble key value type*/

typedef struct {
  esp_bd_addr_t bd_addr;           /*!< peer address */
  esp_ble_key_type_t key_type;     /*!< key type of the security link */
  esp_ble_key_value_t p_key_value; /*!< the pointer to the key value */
} esp_ble_key_t;                   /*!< the union to the ble key value type*/

/**
 * @brief  structure type of the ble local id keys value
 */
typedef struct {
  esp_bt_octet16_t ir;                            /*!< the 16 bits of the ir value */
  esp_bt_octet16_t irk;                           /*!< the 16 bits of the ir key value */
  esp_bt_octet16_t dhk;                           /*!< the 16 bits of the dh key value */
} esp_ble_local_id_keys_t;                        /*!< the structure of the ble local id keys value type*/
typedef uint8_t esp_ble_auth_req_t;               /*!< combination of the above bit pattern */
typedef uint8_t esp_link_key[ESP_BT_OCTET16_LEN]; /* Link Key */
typedef struct {
  esp_bd_addr_t bd_addr;         /*!< BD address peer device. */
  bool key_present;              /*!< Valid link key value in key element */
  esp_link_key key;              /*!< Link key associated with peer device. */
  uint8_t key_type;              /*!< The type of Link Key */
  bool success;                  /*!< TRUE of authentication succeeded, FALSE if failed. */
  uint8_t fail_reason;           /*!< The HCI reason/error code for when success=FALSE */
  esp_ble_addr_type_t addr_type; /*!< Peer device address type */
  esp_bt_dev_type_t dev_type;    /*!< Device type */
  esp_ble_auth_req_t auth_mode;  /*!< authentication mode */
} esp_ble_auth_cmpl_t;           /*!< The ble authentication complete cb type */

typedef union {
  esp_ble_sec_key_notif_t key_notif;   /*!< passkey notification */
  esp_ble_sec_req_t ble_req;           /*!< BLE SMP related request */
  esp_ble_key_t ble_key;               /*!< BLE SMP keys used when pairing */
  esp_ble_local_id_keys_t ble_id_keys; /*!< BLE IR event */
  esp_ble_auth_cmpl_t auth_cmpl;       /*!< Authentication complete indication. */
} esp_ble_sec_t;                       /*!< BLE security type */

typedef union {
  /**
   * @brief ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT
   */
  struct ble_adv_data_cmpl_evt_param {
    esp_bt_status_t status; /*!< Indicate the set advertising data operation success status */
  } adv_data_cmpl;          /*!< Event parameter of ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT */
  /**
   * @brief ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT
   */
  struct ble_scan_rsp_data_cmpl_evt_param {
    esp_bt_status_t status; /*!< Indicate the set scan response data operation success status */
  } scan_rsp_data_cmpl;     /*!< Event parameter of ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT */
  /**
   * @brief ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT
   */
  struct ble_scan_param_cmpl_evt_param {
    esp_bt_status_t status; /*!< Indicate the set scan param operation success status */
  } scan_param_cmpl;        /*!< Event parameter of ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT */
  /**
   * @brief ESP_GAP_BLE_SCAN_RESULT_EVT
   */
  struct ble_scan_result_evt_param {
    esp_gap_search_evt_t search_evt;   /*!< Search event type */
    esp_bd_addr_t bda;                 /*!< Bluetooth device address which has been searched */
    esp_bt_dev_type_t dev_type;        /*!< Device type */
    esp_ble_addr_type_t ble_addr_type; /*!< Ble device address type */
    esp_ble_evt_type_t ble_evt_type;   /*!< Ble scan result event type */
    int rssi;                          /*!< Searched device's RSSI */
    uint8_t ble_adv[ESP_BLE_ADV_DATA_LEN_MAX + ESP_BLE_SCAN_RSP_DATA_LEN_MAX]; /*!< Received EIR */
    int flag;                                                                  /*!< Advertising data flag bit */
    int num_resps;                                                             /*!< Scan result number */
    uint8_t adv_data_len;                                                      /*!< Adv data length */
    uint8_t scan_rsp_len;                                                      /*!< Scan response length */
    uint32_t num_dis;                                                          /*!< The number of discard packets */
  } scan_rst; /*!< Event parameter of ESP_GAP_BLE_SCAN_RESULT_EVT */
  /**
   * @brief ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT
   */
  struct ble_adv_data_raw_cmpl_evt_param {
    esp_bt_status_t status; /*!< Indicate the set raw advertising data operation success status */
  } adv_data_raw_cmpl;      /*!< Event parameter of ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT */
  /**
   * @brief ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT
   */
  struct ble_scan_rsp_data_raw_cmpl_evt_param {
    esp_bt_status_t status; /*!< Indicate the set raw advertising data operation success status */
  } scan_rsp_data_raw_cmpl; /*!< Event parameter of ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT */
  /**
   * @brief ESP_GAP_BLE_ADV_START_COMPLETE_EVT
   */
  struct ble_adv_start_cmpl_evt_param {
    esp_bt_status_t status; /*!< Indicate advertising start operation success status */
  } adv_start_cmpl;         /*!< Event parameter of ESP_GAP_BLE_ADV_START_COMPLETE_EVT */
  /**
   * @brief ESP_GAP_BLE_SCAN_START_COMPLETE_EVT
   */
  struct ble_scan_start_cmpl_evt_param {
    esp_bt_status_t status; /*!< Indicate scan start operation success status */
  } scan_start_cmpl;        /*!< Event parameter of ESP_GAP_BLE_SCAN_START_COMPLETE_EVT */

  esp_ble_sec_t ble_security; /*!< ble gap security union type */
  /**
   * @brief ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT
   */
  struct ble_scan_stop_cmpl_evt_param {
    esp_bt_status_t status; /*!< Indicate scan stop operation success status */
  } scan_stop_cmpl;         /*!< Event parameter of ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT */
  /**
   * @brief ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT
   */
  struct ble_adv_stop_cmpl_evt_param {
    esp_bt_status_t status; /*!< Indicate adv stop operation success status */
  } adv_stop_cmpl;          /*!< Event parameter of ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT */
  /**
   * @brief ESP_GAP_BLE_SET_STATIC_RAND_ADDR_EVT
   */
  struct ble_set_rand_cmpl_evt_param {
    esp_bt_status_t status; /*!< Indicate set static rand address operation success status */
  } set_rand_addr_cmpl;     /*!< Event parameter of ESP_GAP_BLE_SET_STATIC_RAND_ADDR_EVT */
  /**
   * @brief ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT
   */
  struct ble_update_conn_params_evt_param {
    esp_bt_status_t status; /*!< Indicate update connection parameters success status */
    esp_bd_addr_t bda;      /*!< Bluetooth device address */
    uint16_t min_int;       /*!< Min connection interval */
    uint16_t max_int;       /*!< Max connection interval */
    uint16_t latency;   /*!< Slave latency for the connection in number of connection events. Range: 0x0000 to 0x01F3 */
    uint16_t conn_int;  /*!< Current connection interval */
    uint16_t timeout;   /*!< Supervision timeout for the LE Link. Range: 0x000A to 0x0C80.
                              Mandatory Range: 0x000A to 0x0C80 Time = N * 10 msec */
  } update_conn_params; /*!< Event parameter of ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT */
  /**
   * @brief ESP_GAP_BLE_SET_PKT_LENGTH_COMPLETE_EVT
   */
  struct ble_pkt_data_length_cmpl_evt_param {
    esp_bt_status_t status;                  /*!< Indicate the set pkt data length operation success status */
    esp_ble_pkt_data_length_params_t params; /*!<  pkt data length value */
  } pkt_data_lenth_cmpl;                     /*!< Event parameter of ESP_GAP_BLE_SET_PKT_LENGTH_COMPLETE_EVT */
  /**
   * @brief ESP_GAP_BLE_SET_LOCAL_PRIVACY_COMPLETE_EVT
   */
  struct ble_local_privacy_cmpl_evt_param {
    esp_bt_status_t status; /*!< Indicate the set local privacy operation success status */
  } local_privacy_cmpl;     /*!< Event parameter of ESP_GAP_BLE_SET_LOCAL_PRIVACY_COMPLETE_EVT */
  /**
   * @brief ESP_GAP_BLE_REMOVE_BOND_DEV_COMPLETE_EVT
   */
  struct ble_remove_bond_dev_cmpl_evt_param {
    esp_bt_status_t status; /*!< Indicate the remove bond device operation success status */
    esp_bd_addr_t bd_addr;  /*!< The device address which has been remove from the bond list */
  } remove_bond_dev_cmpl;   /*!< Event parameter of ESP_GAP_BLE_REMOVE_BOND_DEV_COMPLETE_EVT */
  /**
   * @brief ESP_GAP_BLE_CLEAR_BOND_DEV_COMPLETE_EVT
   */
  struct ble_clear_bond_dev_cmpl_evt_param {
    esp_bt_status_t status; /*!< Indicate the clear bond device operation success status */
  } clear_bond_dev_cmpl;    /*!< Event parameter of ESP_GAP_BLE_CLEAR_BOND_DEV_COMPLETE_EVT */
  /**
   * @brief ESP_GAP_BLE_GET_BOND_DEV_COMPLETE_EVT
   */
  struct ble_get_bond_dev_cmpl_evt_param {
    esp_bt_status_t status;       /*!< Indicate the get bond device operation success status */
    uint8_t dev_num;              /*!< Indicate the get number device in the bond list */
    esp_ble_bond_dev_t *bond_dev; /*!< the pointer to the bond device Structure */
  } get_bond_dev_cmpl;            /*!< Event parameter of ESP_GAP_BLE_GET_BOND_DEV_COMPLETE_EVT */
  /**
   * @brief ESP_GAP_BLE_READ_RSSI_COMPLETE_EVT
   */
  struct ble_read_rssi_cmpl_evt_param {
    esp_bt_status_t status;    /*!< Indicate the read adv tx power operation success status */
    int8_t rssi;               /*!< The ble remote device rssi value, the range is from -127 to 20, the unit is dbm,
                                        if the RSSI cannot be read, the RSSI metric shall be set to 127. */
    esp_bd_addr_t remote_addr; /*!< The remote device address */
  } read_rssi_cmpl;            /*!< Event parameter of ESP_GAP_BLE_READ_RSSI_COMPLETE_EVT */
  /**
   * @brief ESP_GAP_BLE_UPDATE_WHITELIST_COMPLETE_EVT
   */
  struct ble_update_whitelist_cmpl_evt_param {
    esp_bt_status_t status; /*!< Indicate the add or remove whitelist operation success status */
    esp_ble_wl_opration_t
        wl_opration;       /*!< The value is ESP_BLE_WHITELIST_ADD if add address to whitelist operation success,
                              ESP_BLE_WHITELIST_REMOVE if remove address from the whitelist operation success */
  } update_whitelist_cmpl; /*!< Event parameter of ESP_GAP_BLE_UPDATE_WHITELIST_COMPLETE_EVT */
  /**
   * @brief ESP_GAP_BLE_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_COMPLETE_EVT
   */
  struct ble_update_duplicate_exceptional_list_cmpl_evt_param {
    esp_bt_status_t status;           /*!< Indicate update duplicate scan exceptional list operation success status */
    uint8_t subcode;                  /*!< Define in esp_bt_duplicate_exceptional_subcode_type_t */
    uint16_t length;                  /*!< The length of device_info */
    esp_duplicate_info_t device_info; /*!< device information, when subcode is ESP_BLE_DUPLICATE_EXCEPTIONAL_LIST_CLEAN,
                                         the value is invalid */
  } update_duplicate_exceptional_list_cmpl; /*!< Event parameter of
                                               ESP_GAP_BLE_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_COMPLETE_EVT */
  /**
   * @brief ESP_GAP_BLE_SET_CHANNELS_EVT
   */
  struct ble_set_channels_evt_param {
    esp_bt_status_t stat; /*!< BLE set channel status */
  } ble_set_channels;     /*!< Event parameter of ESP_GAP_BLE_SET_CHANNELS_EVT */
} esp_ble_gap_cb_param_t;
typedef uint8_t esp_ble_auth_req_t; /*!< combination of the above bit pattern */
typedef uint8_t esp_ble_io_cap_t;   /*!< combination of the io capability */
typedef void (*esp_gap_ble_cb_t)(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);

esp_err_t esp_ble_gap_register_callback(esp_gap_ble_cb_t callback);
esp_err_t esp_ble_gap_set_device_name(const char *name);
esp_err_t esp_ble_gap_config_adv_data(esp_ble_adv_data_t *adv_data);
esp_err_t esp_ble_gap_start_advertising(esp_ble_adv_params_t *adv_params);
esp_err_t esp_ble_gap_set_security_param(esp_ble_sm_param_t param_type, void *value, uint8_t len);
esp_err_t esp_ble_gap_security_rsp(esp_bd_addr_t bd_addr, bool accept);
#ifdef __cplusplus
}
#endif