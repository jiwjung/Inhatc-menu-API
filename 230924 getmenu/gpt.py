import requests

# POST 요청을 보낼 URL
url = "https://inha.ac.kr/diet/kr/2/view.do"  # 실제 URL로 변경

# 데이터를 포함하는 딕셔너리 생성
data = {
    "layout": "J3sRfz6SuHMYDlWbLXHbgQ%3D%3D",
    "monday": "2023.09.18",
    "week": "week"
}

# POST 요청 보내기
response = requests.post(url, data=data)

# 응답 확인
if response.status_code == 200:
    print("요청 성공!")
    print("서버 응답:", response.text)

    print(len(response.text))
else:
    print("요청 실패. 상태 코드:", response.status_code)

