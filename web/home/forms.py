from django import forms
from django.db import models as d_models
from django.contrib.auth import forms as auth_forms

import models

class LoginForm( auth_forms.AuthenticationForm ):
    pass

class TeamRegistrationForm( forms.Form ):
    name = forms.CharField( max_length=100 )
    email = forms.EmailField( max_length=100 )
    password = forms.CharField( widget = forms.PasswordInput, max_length=100 )
    password_verify = forms.CharField( widget = forms.PasswordInput, max_length=100 )

    def clean_password_verify(self):
        if self.cleaned_data["password_verify"] != self.cleaned_data["password"]:
            raise forms.ValidationError('Passwords did not match')

class MemberRegistrationForm( forms.Form ):
    name = forms.CharField( max_length=100 )
    rollNumber = forms.CharField( max_length=20 )

class ForgotPasswordForm( forms.Form ):
    name = forms.CharField( max_length=100 )
    email = forms.CharField( max_length=100 )

# TODO: Forms to modify teams

