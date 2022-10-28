#include "usb_device.h"
#include "usbd_hid.h"

extern USBD_HandleTypeDef hUsbDeviceFS;

static uint8_t keyBoardHIDsub[] = {0, 0, 0, 0, 0, 0, 0, 0};

void keyboard_print(char *data, uint16_t length) {
  for (uint16_t count = 0; count < length; count++) {
    if (data[count] >= 0x41 && data[count] <= 0x5A) {
      keyBoardHIDsub[0] = 0x02;
      keyBoardHIDsub[2] = data[count] - 0x3D;
      USBD_HID_SendReport(&hUsbDeviceFS, keyBoardHIDsub,
                          sizeof(keyBoardHIDsub));
      HAL_Delay(15);
      keyBoardHIDsub[0] = 0x00;
      keyBoardHIDsub[2] = 0x00;
      USBD_HID_SendReport(&hUsbDeviceFS, keyBoardHIDsub,
                          sizeof(keyBoardHIDsub));
    } else if (data[count] >= 0x61 && data[count] <= 0x7A) {
      keyBoardHIDsub[2] = data[count] - 0x5D;
      USBD_HID_SendReport(&hUsbDeviceFS, keyBoardHIDsub,
                          sizeof(keyBoardHIDsub));
      HAL_Delay(15);
      keyBoardHIDsub[2] = 0x00;
      USBD_HID_SendReport(&hUsbDeviceFS, keyBoardHIDsub,
                          sizeof(keyBoardHIDsub));
    } else if (data[count] == 0x20) {
      keyBoardHIDsub[2] = 0x2C;
      USBD_HID_SendReport(&hUsbDeviceFS, keyBoardHIDsub,
                          sizeof(keyBoardHIDsub));
      HAL_Delay(15);
      keyBoardHIDsub[2] = 0x00;
      USBD_HID_SendReport(&hUsbDeviceFS, keyBoardHIDsub,
                          sizeof(keyBoardHIDsub));
    } else if (data[count] == 0x0A) {
      keyBoardHIDsub[2] = 0x28;
      USBD_HID_SendReport(&hUsbDeviceFS, keyBoardHIDsub,
                          sizeof(keyBoardHIDsub));
      HAL_Delay(15);
      keyBoardHIDsub[2] = 0x00;
      USBD_HID_SendReport(&hUsbDeviceFS, keyBoardHIDsub,
                          sizeof(keyBoardHIDsub));
    }
    HAL_Delay(25);
  }
}
