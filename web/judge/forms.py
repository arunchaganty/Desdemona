from django import forms
from django.db import models as d_models

import models

import hashlib

class SubmissionForm( forms.ModelForm ):
    data = forms.FileField(label="Bot Binary")
    class Meta:
        model = models.Submission
        exclude = ('timestamp','team', 'sha1sum')

    def clean(self):
        forms.ModelForm.clean(self)
        self.clean_sha1sum()
        self.cleaned_data["data"].name = self.cleaned_data["sha1sum"]
        self.instance.sha1sum = self.cleaned_data["sha1sum"]
        return self.cleaned_data

    def clean_sha1sum(self):
        data = self.cleaned_data["data"]
        self.cleaned_data["sha1sum"] = hashlib.sha1(data.read()).hexdigest()
        print self.cleaned_data

