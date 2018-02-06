from django.shortcuts import render
from django.http import HttpResponse
from django.template import RequestContext, loader
from django.core.mail import send_mail

from django.views.decorators.clickjacking import xframe_options_exempt
import smtplib

@xframe_options_exempt
def index(request):
    template = loader.get_template('homepage/index.html')
    context = RequestContext(request, {})
    return HttpResponse(template.render(context))

@xframe_options_exempt
def email(request):
    print ("kqwjrlqk")
    print (request)
    if request.method == 'POST':
        sender_name = request.POST.get('name')
        sender_email = request.POST.get('email')
        sender_phone = request.POST.get('phone')
        message = request.POST.get('message')

        if not send_email(sender_name, sender_email, sender_phone, message):
            fo = open("failed_email.txt", "wb")
            fo.write(sender_name)
            fo.write(sender_email)
            fo.write(message)
            fo.close()
        return redirect('contact')

def send_email(sender_name, sender_email, sender_phone, message):
    if sender_name and sender_email and sender_phone and message:
        to = 'hyunwoo.na@gmail.com'
        email_subject = "Website Contact Form: " + sender_name
        email_body = "You have received a new message from your website contact "\
                      + "form.\n\n Here are the details:\n\nName: " + sender_name\
                      + "\n\nEmail:                   " + sender_email\
                      + "\n\nPhone: " + sender_phone +"\n\nMessage:\n" + message

        try:
            send_mail(email_subject, email_body, sender_email,
                ['hyunwoo.na@gmail.com', ], fail_silently=False)
        except smtplib.SMTPException:
            return False
        return True

    return False
