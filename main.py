import cv2
import mediapipe as mp
from cvzone.HandTrackingModule import HandDetector
import socket

width, height = 1280, 720
cap = cv2.VideoCapture(0)
cap.set(3, width)  # Set width
cap.set(4, height)   # Set height (optional, but recommended to set both)

detector = HandDetector(maxHands=1, detectionCon=0.8)  # Fixed typo

sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
serverAddressPort = ("127.0.0.1",5052)

while True:
    success, img = cap.read()
    hands, img = detector.findHands(img)
    data = []

    if hands:
        hand = hands[0]
        lmList = hand['lmList']
        print(lmList)
        print("\n")
        for lm in lmList:
            data.extend([lm[0],height-lm[1],lm[2]])
        print(data)
        print("\n")
        sock.sendto(str.encode(str(data)),serverAddressPort)
    img = cv2.resize(img,(0,0),None, 0.5, 0.5)
    cv2.imshow("image", img)
    cv2.waitKey(1)