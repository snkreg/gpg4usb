/*
 *      keygendialog.h
 *
 *      Copyright 2008 gpg4usb-team <gpg4usb@cpunk.de>
 *
 *      This file is part of gpg4usb.
 *
 *      Gpg4usb is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      Gpg4usb is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with gpg4usb.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef __KEYGENDIALOG_H__
#define __KEYGENDIALOG_H__

#include "keygenthread.h"
#include "gpgcontext.h"
#include <QtGui>

QT_BEGIN_NAMESPACE
class QDateTime;
class QDialogButtonBox;
class QDialog;
class QGridLayout;
QT_END_NAMESPACE

class KeyGenDialog : public QDialog
{
    Q_OBJECT

public:
    KeyGenDialog(GpgME::GpgContext* ctx, QWidget *parent = 0);

private:
    void generateKeyDialog();

    /**
     * @details Check the password strength of the text in the passwordEdit member
     *
     * @return digit between 0 and 6, the higher the more secure is the password
     */
    int checkPassWordStrength();

    GpgME::GpgContext *mCtx; /** The current gpg context */
    KeyGenThread *keyGenThread; /** Thread for key generation */
    QStringList errorMessages; /** List of errors occuring when checking entries of lineedits */
    QDialogButtonBox *buttonBox; /** Box for standardbuttons */
    QLabel *errorLabel; /** Label containing error message */
    QLineEdit *nameEdit; /** Lineedit for the keys name */
    QLineEdit *emailEdit; /** Lineedit for the keys email */
    QLineEdit *commentEdit; /** Lineedit for the keys comment */
    QLineEdit *passwordEdit; /** Lineedit for the keys password */
    QLineEdit *repeatpwEdit; /** Lineedit for the repetition of the keys password */
    QSpinBox *keySizeSpinBox; /** Spinbox for the keys size (in bit) */
    QComboBox *keyTypeComboBox; /** Combobox for Keytpe */
    QDateTimeEdit *dateEdit; /** Dateedit for expiration date */
    QCheckBox *expireCheckBox; /** Checkbox, if key should expire */
    QSlider *pwStrengthSlider; /** Slider showing the password strength */
    int lastKeySize; /** integer to remember to last selected keysize (only display warning first tim above 2048)*/
private slots:
    /**
     * @details when expirebox was checked/unchecked, enable/disable the expiration date box
     */
    void expireBoxChanged();

    /**
     * @details When passwordedit changed, set new value for password strength slider
     */
    void passwordEditChanged();

    /**
     * @details When keysize changed, show message, when too large
     */
    void keySizeChanged();

    /**
     * @details When passwordedit changed, set keysize appropriately
     */
    void keyTypeChanged();

    /**
     * @details check all lineedits for false entries. Show error, when there is one, otherwise generate the key
     */
    void keyGenAccept();

};
#endif // __KEYGENDIALOG_H__
