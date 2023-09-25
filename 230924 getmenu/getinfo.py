import datetime

def menuDates():
    today = datetime.date.today()
    current_weekday = today.weekday()

    if current_weekday <= 4:  # 월요일부터 금요일까지
        days_until_monday = current_weekday * (-1)
    else:  # 토요일 또는 일요일
        days_until_monday = 7 - current_weekday

    monday = today + datetime.timedelta(days=days_until_monday)
    saturday = monday + datetime.timedelta(days=5)

    return monday.strftime("%Y%m%d"), saturday.strftime("%Y%m%d")
