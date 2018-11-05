from __future__ import print_function
import cv2 as cv
import argparse
max_value = 255
max_value_H = 360//2
low_H = 0
low_L = 0
low_S = 0
high_H = max_value_H
high_L = max_value
high_S = max_value
window_capture_name = 'Video Capture'
window_detection_name = 'Object Detection'
low_H_name = 'Low H'
low_L_name = 'Low L'
low_S_name = 'Low S'
high_H_name = 'High H'
high_L_name = 'High L'
high_S_name = 'High S'
def on_low_H_thresh_trackbar(val):
    global low_H
    global high_H
    low_H = val
    low_H = min(high_H-1, low_H)
    cv.setTrackbarPos(low_H_name, window_detection_name, low_H)
def on_high_H_thresh_trackbar(val):
    global low_H
    global high_H
    high_H = val
    high_H = max(high_H, low_H+1)
    cv.setTrackbarPos(high_H_name, window_detection_name, high_H)
def on_low_L_thresh_trackbar(val):
    global low_L
    global high_L
    low_L = val
    low_L = min(high_L-1, low_L)
    cv.setTrackbarPos(low_L_name, window_detection_name, low_L)
def on_high_L_thresh_trackbar(val):
    global low_L
    global high_L
    high_L = val
    high_L = max(high_L, low_L+1)
    cv.setTrackbarPos(high_L_name, window_detection_name, high_L)
def on_low_S_thresh_trackbar(val):
    global low_S
    global high_S
    low_S = val
    low_S = min(high_S-1, low_S)
    cv.setTrackbarPos(low_S_name, window_detection_name, low_S)
def on_high_S_thresh_trackbar(val):
    global low_S
    global high_S
    high_S = val
    high_S = max(high_S, low_S+1)
    cv.setTrackbarPos(high_S_name, window_detection_name, high_S)
parser = argparse.ArgumentParser(description='Code for Thresholding Operations using inRange tutorial.')
parser.add_argument('--camera', help='Camera devide number.', default=0, type=int)
args = parser.parse_args()
cap = cv.VideoCapture('../Bola-2-Larc2018-Apartamento.avi')
cv.namedWindow(window_capture_name)
cv.namedWindow(window_detection_name)
cv.createTrackbar(low_H_name, window_detection_name , low_H, max_value_H, on_low_H_thresh_trackbar)
cv.createTrackbar(high_H_name, window_detection_name , high_H, max_value_H, on_high_H_thresh_trackbar)
cv.createTrackbar(low_L_name, window_detection_name , low_L, max_value, on_low_L_thresh_trackbar)
cv.createTrackbar(high_L_name, window_detection_name , high_L, max_value, on_high_L_thresh_trackbar)
cv.createTrackbar(low_S_name, window_detection_name , low_S, max_value, on_low_S_thresh_trackbar)
cv.createTrackbar(high_S_name, window_detection_name , high_S, max_value, on_high_S_thresh_trackbar)
while True:
    
    ret, frame = cap.read()
    if frame is None:
        break
    frame_HLS = cv.cvtColor(frame, cv.COLOR_BGR2HLS)
    frame_threshold = cv.inRange(frame_HLS, (low_H, low_L, low_S), (high_H, high_L, high_S))
    
    
    cv.imshow(window_capture_name, frame)
    cv.imshow(window_detection_name, frame_threshold)
    
    key = cv.waitKey(0)
    if key == ord('q') or key == 27:
        break