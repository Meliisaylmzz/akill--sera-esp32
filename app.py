import streamlit as st
import pandas as pd

st.set_page_config(page_title="Akıllı Sera Paneli", page_icon="🌱")

st.title("🌱 Akıllı Sera İklim Kontrolü")
st.caption("ESP32 + DHT22 + Servo (Wokwi simülasyonu)")

ESIK = 30.0

satirlar = []
with open("veri.txt", encoding="utf-8", errors="ignore") as f:
    for satir in f:
        parcalar = satir.strip().split(",")
        if len(parcalar) == 3:
            try:
                satirlar.append([float(p) for p in parcalar])
            except ValueError:
                pass

df = pd.DataFrame(satirlar, columns=["sicaklik", "nem", "pencere"])

if df.empty:
    st.error("veri.txt içinde okunabilir veri bulunamadı.")
    st.stop()

df["esik"] = ESIK

son = df.iloc[-1]

col1, col2, col3 = st.columns(3)
col1.metric("Son sıcaklık", f"{son['sicaklik']:.1f} °C")
col2.metric("Son nem", f"{son['nem']:.0f} %")
col3.metric("Pencere", "AÇIK" if son["pencere"] == 1 else "KAPALI")

st.subheader("Sıcaklık ve eşik değeri")
st.line_chart(df[["sicaklik", "esik"]])

st.subheader("Nem")
st.line_chart(df[["nem"]])

acik_oran = df["pencere"].mean() * 100
st.info(f"Ölçümlerin %{acik_oran:.0f}'inde pencere açıktı. Eşik: {ESIK} °C")

st.subheader("Ham veri")
st.dataframe(df[["sicaklik", "nem", "pencere"]])